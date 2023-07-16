//
//  GameBoard.cpp
//  Combine Number
//
//  Created by Harry Nguyen on 12/7/23.
//

#include "GameBoard.h"
#include "GameConfig.h"
#include "RandomNumber.h"
#include "ColorFactory.h"

GameBoard::GameBoard(int rows, int columns) {
  this->rows = rows;
  this->columns = columns;
  this->size = Size(rows* WIDTH_HEIGHT_CELL, columns* WIDTH_HEIGHT_CELL);
  this->resetGame();
}

void GameBoard::resetGame() {
  isTouchAvailable = true;
  totalNumberNeedFillUp = rows * columns;
  earnPoint = 0;
  maximumNumber = 2;
  cleanNumbers();
  drawFirstGameBoard();
}
void GameBoard::cleanNumbers() {
  for(int row = 0; row < rows; row++ ) {
    for(int column = 0; column < columns; column++) {
      if(numberObjects[row][column] != nullptr) {
        removeChild(numberObjects[row][column]);
        numberObjects[row][column] = nullptr;
      }
    }
  }
}

GameBoard::~GameBoard() {
  delegate = nullptr;
}

void GameBoard::setDelegate(GameBoardDelegate* delegate) {
  this->delegate = delegate;
}

Vec2 GameBoard::convertMatrixToGameBoardPosition(int row, int column) {
  float xPosition = row * WIDTH_HEIGHT_CELL;
  float yPosition = column * WIDTH_HEIGHT_CELL;
  return Vec2(xPosition, yPosition);
}

Vec2 GameBoard::convertPositionToGameBoardMatrix(const Vec2& position) {
  int x = position.x / WIDTH_HEIGHT_CELL;
  int y = position.y / WIDTH_HEIGHT_CELL;
  return Vec2(x, y);
}

Vec2 GameBoard::convertTouchToGameBoardPosition(Touch* mTouch) {
  Vec2 touchPosition = mTouch->getLocation();
  Vec2 pos = Vec2(touchPosition.x - getPositionX(), touchPosition.y - getPositionY());
  return pos;
}

bool GameBoard::handleTouchBegan(Touch* mTouch, Event* pEvent) {
  if(!isTouchAvailable) { return false; };
  Vec2 pos = convertTouchToGameBoardPosition(mTouch);
  if(!isTouchingInsideGameBoard(pos)) { return false; }
  Vec2 matrix = convertPositionToGameBoardMatrix(pos);
  NumberObject* touchNumber = getTouchNumberObject(matrix.x, matrix.y);
  if(touchNumber == nullptr) { return  false;}
  highLightSameNumber(touchNumber);
  touchNumber->setAnimationStatus(TOUCH_ANIMATION);
  stackTouchNumbers.push(touchNumber);
  return true;
}

void GameBoard::handleTouchMove(Touch* mTouch, Event* pEvent) {
  if(stackTouchNumbers.empty()) { return;}
  
  Vec2 matrix = convertPositionToGameBoardMatrix(convertTouchToGameBoardPosition(mTouch));
  NumberObject* touchNumber = getTouchNumberObject(matrix.x, matrix.y);
  if(touchNumber == nullptr) { return ;}
  NumberObject* headStack = stackTouchNumbers.top();
  if(touchNumber == headStack) { return; }
  
  if(existNumberOnStacks(touchNumber)) {
    stack<NumberObject*> tempStack = stackTouchNumbers;
    tempStack.pop();
    NumberObject* newHead = tempStack.top();
    if(newHead == touchNumber) {
      headStack->setAnimationStatus(REVERT_ANIMATION_AFTER_TOUCH);
      stackTouchNumbers.pop();
      removeLineWhenMove(newHead->getMatrix(), headStack->getMatrix());
    }
  } else {
    if (abilityConnect(touchNumber, headStack)) {
      touchNumber->setAnimationStatus(TOUCH_ANIMATION);
      stackTouchNumbers.push(touchNumber);
      addLineWhenMove(headStack->getMatrix(), touchNumber->getMatrix());
    }
  }
}

void GameBoard::handleTouchEnd(Touch* mTouch, Event* pEvent) {
  if(stackTouchNumbers.empty()) {return;}
  auto handleTouchStackWhenTouchEndedCallFunc = CallFunc::create([&, this]() { handleTouchStackWhenTouchEnded(); });
  auto revertHighLightNumberCallFunc = CallFunc::create([&, this]() { revertHighLightNumber(); });
  auto sequence = Sequence::create(handleTouchStackWhenTouchEndedCallFunc, revertHighLightNumberCallFunc, nullptr);
  runAction(sequence);
}

void GameBoard::handleTouchStackWhenTouchEnded() {
  if(stackTouchNumbers.size() >= MIN_SAME_VALUE) {
    handleConnectNumber([&, this]{
      this->handleDropNumber();
      this->fillUpGameBoard();
      if(delegate != nullptr) {
        this->delegate->fireEarnScore(earnPoint);
        this->delegate->fireMaximumNumber(maximumNumber);
      };
    });
  } else {
    while (!stackTouchNumbers.empty()) {
      NumberObject* headStack = stackTouchNumbers.top();
      headStack->setAnimationStatus(REVERT_ANIMATION_AFTER_TOUCH);
      stackTouchNumbers.pop();
    }
  }
  removeAllLines();
}

void GameBoard::handleConnectNumber(function<void()> completion) {
  NumberObject* rootStack = nullptr;
  int countMoveToAnimation = int(stackTouchNumbers.size());
  while (!stackTouchNumbers.empty()) {
    NumberObject* head = stackTouchNumbers.top();
    if(rootStack == nullptr) {
      rootStack = head;
    } else {
      totalNumberNeedFillUp += 1;
      earnPoint += head->getValue();
      head->runMoveToAndDisAppearAnimation(head->getPosition(),
                                           convertMatrixToGameBoardPosition(rootStack->getMatrix().x, rootStack->getMatrix().y), [&, this, head, rootStack, countMoveToAnimation, completion]{
        numberObjects[int(head->getMatrix().x)][int(head->getMatrix().y)] = nullptr;
        if(countMoveToAnimation == 1) {
          if(rootStack == nullptr) { return; }
          int newValue = rootStack->getValue() + 1;
          maximumNumber = max(maximumNumber, newValue);
          earnPoint += rootStack->getValue();
          numberObjects[int(rootStack->getMatrix().x)][int(rootStack->getMatrix().y)]->runIncreaseNumberAnimation(newValue,
                                                                                                                  ColorFactory::GetInstance()->getTextColor(),
                                                                                                                  ColorFactory::GetInstance()->getCircleColor(newValue),
                                                                                                                  completion);
        }
      });
    }
    stackTouchNumbers.pop();
    countMoveToAnimation -= 1;
  }
}

void GameBoard::handleDropNumber() {
  for(int i = 0; i < TOTAL_ROW_CELL; i++) {
    int numberOfEmptySpace = 0;
    for(int j = 0; j < TOTAL_COLUMN_CELL; j++) {
      NumberObject* number = numberObjects[i][j];
      if(number == nullptr) {
        numberOfEmptySpace += 1;
      } else {
        NumberObject* temp = numberObjects[i][j];
        numberObjects[i][j] = nullptr;
        
        numberObjects[i][j - numberOfEmptySpace] = temp;
        numberObjects[i][j - numberOfEmptySpace]->setMatrix(Vec2(i, j - numberOfEmptySpace));
        numberObjects[i][j - numberOfEmptySpace]->setPosition(convertMatrixToGameBoardPosition(i, j - numberOfEmptySpace));
        
        j -= numberOfEmptySpace;
        numberOfEmptySpace = 0;
      }
    }
  }
}

vector<int> GameBoard::getAllAvailableNumberOnGameBoard() {
  std::vector<int> numbers;
  for(int row = 0; row < TOTAL_ROW_CELL; row++) {
    for(int column = 0; column < TOTAL_COLUMN_CELL; column++) {
      if(numberObjects[row][column] != nullptr) {
        int value = numberObjects[row][column]->getValue();
        auto it = std::find(numbers.begin(), numbers.end(), value);
        if (it == numbers.end()) {
          numbers.push_back(value);
        }
      }
    }
  }
  return numbers;
}

void GameBoard::fillUpGameBoard() {
  vector<int> buckets = getAllAvailableNumberOnGameBoard();
  for(int row = 0; row < TOTAL_ROW_CELL; row++) {
    for(int column = 0; column < TOTAL_COLUMN_CELL; column++) {
      if(numberObjects[row][column] == nullptr) {
        int number = RandomNumber::GetInstance()->getRandomNumber(buckets);
        drawNumber(number, row, column, ColorFactory::GetInstance()->getTextColor(), ColorFactory::GetInstance()->getCircleColor(number), [&, this]{
          this->totalNumberNeedFillUp -= 1;
          if(totalNumberNeedFillUp == 0) { this->checkGameOver(); }
        });
      }
    }
  }
}

void GameBoard::drawFirstGameBoard() {
  for(int row = 0; row < rows; row++) {
    for(int column = 0; column < columns; column++) {
      int number = RandomNumber::GetInstance()->getRandomNumber(maximumNumber - 1);
      drawNumber(number, row, column,
                 ColorFactory::GetInstance()->getTextColor(),
                 ColorFactory::GetInstance()->getCircleColor(number), [&, this]{
        this->totalNumberNeedFillUp -= 1;
        if(totalNumberNeedFillUp == 0) {
          if(UserDefault::getInstance()->getBoolForKey(KEY_FRIST_TIME_OPEN_GAME, true)) {
            this->showGuideLineLayer(FIRST_TIME_OPEN);
          } else {
            if(this->delegate != nullptr) { this->delegate->readyToShowAdvertisement(); };
          }
        }
      });
    }
  }
}

void GameBoard::showGuideLineLayer(int status) {
  switch (status) {
    case CLICK_SUGGESTION: break;
    case FIRST_TIME_OPEN:
      if(delegate != nullptr) { delegate->fireShowGuidePopUp(true); };
      break;
    default: break;
  }
  isTouchAvailable = false;
  vector<Vec2> connectPoints = getAllAbilityConnectPoints();
  if(connectPoints.size() < MIN_SAME_VALUE)  { return; }
  auto sprite = Sprite::create(GUIDE_ICON_NAME);
  Vec2 position = convertMatrixToGameBoardPosition(connectPoints[0].x, connectPoints[0].y);
  sprite->setPosition(Vec2(position.x + WIDTH_HEIGHT_CELL/2.0, position.y));
  sprite->setLocalZOrder(GUIDE_ICON_TAG);
  this->addChild(sprite);
  float duration = (max(int(connectPoints.size()/4), 1) * GUIDE_LINE_MOVE_TO_DURATION)/(connectPoints.size());
  moveGuideSpriteToPoints(sprite, connectPoints, duration, [&, sprite, status, this]{
    if(this->delegate != nullptr) {
      switch (status) {
        case CLICK_SUGGESTION: break;
        case FIRST_TIME_OPEN:
          this->delegate->fireShowGuidePopUp(false);
          this->delegate->readyToShowAdvertisement();
          break;
        default: break;
      }
      this->delegate->activeTouchTopBarMenuLayer();
    };
    this->removeAllLines();
    this->isTouchAvailable = true;
    this->removeChild(sprite);
    UserDefault::getInstance()->setBoolForKey(KEY_FRIST_TIME_OPEN_GAME, false);
  });
}

void GameBoard::moveGuideSpriteToPoints(Sprite* sprite, const std::vector<Vec2>& points, float duration, function<void()> completion) {
  Vector<FiniteTimeAction*> actions;
  for(int i = 0; i < points.size(); i++) {
    Vec2 position = convertMatrixToGameBoardPosition(points[i].x, points[i].y);
    auto moveTo = MoveTo::create(duration, Vec2(position.x + WIDTH_HEIGHT_CELL/2.0, position.y));
    actions.pushBack(moveTo);
    if(i + 1 < points.size()) { addLineWhenMove(points[i], points[i+1]); }
  }
  auto disappear = CallFunc::create([sprite]() { sprite->setVisible(false); });
  actions.pushBack(disappear);
  
  auto completionAction = CallFunc::create([&, completion]() { completion(); });
  actions.pushBack(completionAction);
  
  auto sequence = Sequence::create(actions);
  sprite->runAction(sequence);
}

void GameBoard::drawNumber(int value, int row, int column, Color3B textColor, Color4F circleColor, function<void()> completion) {
  NumberObject* number = new NumberObject(value, Vec2(row, column), textColor, circleColor);
  number->setPosition(convertMatrixToGameBoardPosition(row, column + TOTAL_COLUMN_CELL));
  number->setLocalZOrder(NUMBER_TAG);
  addChild(number);
  number->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
  number->runMoveToAndAppearAnimation(convertMatrixToGameBoardPosition(row, column + TOTAL_COLUMN_CELL),
                                      convertMatrixToGameBoardPosition(row, column),
                                      completion);
  numberObjects[row][column] = number;
}


bool GameBoard::isTouchingInsideGameBoard(const Vec2& position) {
  if(position.x < 0 ||
     position.x > size.width ||
     position.y < 0 ||
     position.y > size.height) {
    return false;
  } else {
    return true;
  }
}

NumberObject* GameBoard::getTouchNumberObject(int row, int column) {
  for(int i = 0; i < TOTAL_ROW_CELL; i++) {
    for(int j = 0; j < TOTAL_COLUMN_CELL; j++) {
      NumberObject* number = numberObjects[i][j];
      if(number != nullptr && number->getMatrix().x == row && number->getMatrix().y == column) {
        return number;
      }
    }
  }
  return nullptr;
}

void GameBoard::highLightSameNumber(NumberObject* number) {
  for(int row = 0; row < TOTAL_ROW_CELL; row++) {
    for(int column = 0; column < TOTAL_COLUMN_CELL; column++) {
      if(numberObjects[row][column] != nullptr) {
        if(numberObjects[row][column]->getValue() == number->getValue()) {
          numberObjects[row][column]->setActiveNumber(true);
        } else {
          numberObjects[row][column]->setActiveNumber(false);
        }
      }
    }
  }
}

void GameBoard::revertHighLightNumber() {
  for(int row = 0; row < TOTAL_ROW_CELL; row++) {
    for(int column = 0; column < TOTAL_COLUMN_CELL; column++) {
      if(numberObjects[row][column] != nullptr) {
        numberObjects[row][column]->setActiveNumber(true);
      }
    }
  }
}

bool GameBoard::existNumberOnStacks(NumberObject* number) {
  stack<NumberObject*> stacks = stackTouchNumbers;
  while (!stacks.empty()) {
    NumberObject* last = stacks.top();
    if(last == number) {
      return true;
    } else {
      stacks.pop();
    }
  }
  return false;
}

void GameBoard::addLineWhenMove(const Vec2& startMatrix, const Vec2& endMatrix) {
  Vec2 originalStartPoint = convertMatrixToGameBoardPosition(startMatrix.x, startMatrix.y);
  Vec2 originalEndPoint = convertMatrixToGameBoardPosition(endMatrix.x, endMatrix.y);
  
  Vec2 startPoint = Vec2(originalStartPoint.x + WIDTH_HEIGHT_CELL/2.0, originalStartPoint.y + WIDTH_HEIGHT_CELL/2.0);
  Vec2 endPoint = Vec2(originalEndPoint.x + WIDTH_HEIGHT_CELL/2.0, originalEndPoint.y + WIDTH_HEIGHT_CELL/2.0);
  
  DrawNode* drawNode = cocos2d::DrawNode::create();
  drawNode->setLocalZOrder(LINE_TAG);
  addChild(drawNode);
  drawNode->drawSegment(startPoint, endPoint, LINE_WIDTH, ColorFactory::GetInstance()->getLineColor());
  
  DrawLineObject* line = new DrawLineObject(drawNode, startMatrix, endMatrix);
  drawLines.push_back(line);
}

void GameBoard::removeLineWhenMove(const Vec2& startMatrix, const Vec2& endMatrix) {
  for(int index = 0; index < drawLines.size(); index++) {
    DrawLineObject* line = drawLines[index];
    if(line->getStartMatrix() == startMatrix && line->getEndMatrix() == endMatrix) {
      removeChild(line->getDrawNode());
      drawLines.erase(drawLines.begin() + index);
      return;
    }
  }
}

void GameBoard::removeAllLines() {
  for(int index = 0; index < drawLines.size(); index++) {
    DrawLineObject* line = drawLines[index];
    removeChild(line->getDrawNode());
    drawLines.erase(drawLines.begin() + index);
    index -= 1;
  }
}

bool GameBoard::checkGameOver() {
  vector<Vec2> connectPoints = getAllAbilityConnectPoints();
  if(connectPoints.size() >= MIN_SAME_VALUE) {
    return false;
  } else {
    if(delegate != nullptr) { delegate->fireGameOverEvent(); };
    return true;
  }
}

vector<Vec2> GameBoard::getAllAbilityConnectPoints() {
  for(int row = 0; row < TOTAL_ROW_CELL; row++){
    for(int column = 0; column < TOTAL_COLUMN_CELL; column++) {
      vector<Vec2> result = getAbilityConnectPointsAt(row, column);
      result.insert(result.begin(), Vec2(row, column));
      resetTraveledNumber(result);
      if(result.size() >= MIN_SAME_VALUE) {
        return result;
      }
    }
  }
  return vector<Vec2>();
}

vector<Vec2> GameBoard::getAbilityConnectPointsAt(int row, int column) {
  vector<Vec2> emptyVector;
  return dfsCheckAbilityConnect(row, column, emptyVector);
}

void GameBoard::resetTraveledNumber(vector<Vec2> points) {
  for(int i = 0; i < points.size(); i++) {
    Vec2 point = points[i];
    if(numberObjects[int(point.x)][int(point.y)] != nullptr) {
      numberObjects[int(point.x)][int(point.y)]->setTraveled(false);
    }
  }
}

vector<Vec2> GameBoard::dfsCheckAbilityConnect(int row, int column, vector<Vec2>& connectPoints) {
  Vec2 source = Vec2(row, column);
  Vec2 rightEqualX = Vec2(row + 1, column);
  Vec2 topEqualY = Vec2(row, column + 1);
  Vec2 bottomEqualY = Vec2(row, column - 1);
  Vec2 leftUp = Vec2(row - 1, column + 1);
  Vec2 leftDown = Vec2(row - 1, column - 1);
  Vec2 rightUp = Vec2(row + 1, column + 1);
  Vec2 rightDown = Vec2(row + 1, column - 1);
  Vec2 leftEqualX = Vec2(row - 1, column);
  
  if(checkAbilityConnect(source, leftEqualX) == true) { // leftEqualX
    connectPoints.push_back(leftEqualX);
    numberObjects[int(source.x)][int(source.y)]->setTraveled(true);
    numberObjects[int(leftEqualX.x)][int(leftEqualX.y)]->setTraveled(true);
    return dfsCheckAbilityConnect(leftEqualX.x, leftEqualX.y, connectPoints);
  } else if(checkAbilityConnect(source, rightEqualX) == true) { // rightEqualX
    connectPoints.push_back(rightEqualX);
    numberObjects[int(source.x)][int(source.y)]->setTraveled(true);
    numberObjects[int(rightEqualX.x)][int(rightEqualX.y)]->setTraveled(true);
    return dfsCheckAbilityConnect(rightEqualX.x, rightEqualX.y, connectPoints);
  } else if(checkAbilityConnect(source, topEqualY) == true) { // topEqualY
    connectPoints.push_back(topEqualY);
    numberObjects[int(source.x)][int(source.y)]->setTraveled(true);
    numberObjects[int(topEqualY.x)][int(topEqualY.y)]->setTraveled(true);
    return dfsCheckAbilityConnect(topEqualY.x, topEqualY.y, connectPoints);
  } else if(checkAbilityConnect(source, bottomEqualY) == true) {   // bottomEqualY
    connectPoints.push_back(bottomEqualY);
    numberObjects[int(source.x)][int(source.y)]->setTraveled(true);
    numberObjects[int(bottomEqualY.x)][int(bottomEqualY.y)]->setTraveled(true);
    return dfsCheckAbilityConnect(bottomEqualY.x, bottomEqualY.y, connectPoints);
  } else if(checkAbilityConnect(source, leftUp) == true) {   // leftUp
    connectPoints.push_back(leftUp);
    numberObjects[int(source.x)][int(source.y)]->setTraveled(true);
    numberObjects[int(leftUp.x)][int(leftUp.y)]->setTraveled(true);
    return dfsCheckAbilityConnect(leftUp.x, leftUp.y, connectPoints);
  } else if(checkAbilityConnect(source, leftDown) == true) {  // leftDown
    connectPoints.push_back(leftDown);
    numberObjects[int(source.x)][int(source.y)]->setTraveled(true);
    numberObjects[int(leftDown.x)][int(leftDown.y)]->setTraveled(true);
    return dfsCheckAbilityConnect(leftDown.x, leftDown.y, connectPoints);
  } else if(checkAbilityConnect(source, rightUp) == true) {   // rightUp
    connectPoints.push_back(rightUp);
    numberObjects[int(source.x)][int(source.y)]->setTraveled(true);
    numberObjects[int(rightUp.x)][int(rightUp.y)]->setTraveled(true);
    return dfsCheckAbilityConnect(rightUp.x, rightUp.y, connectPoints);
  } else if(checkAbilityConnect(source, rightDown) == true) { // rightDown
    connectPoints.push_back(rightDown);
    numberObjects[int(source.x)][int(source.y)]->setTraveled(true);
    numberObjects[int(rightDown.x)][int(rightDown.y)]->setTraveled(true);
    return dfsCheckAbilityConnect(rightDown.x, rightDown.y, connectPoints);
  } else {
    return connectPoints;
  }
}

bool GameBoard::checkAbilityConnect(const Vec2& startMatrix, const Vec2& endMatrix) {
  if(startMatrix.x < 0 || startMatrix.x >= TOTAL_ROW_CELL ||
     startMatrix.y < 0 || startMatrix.y >= TOTAL_COLUMN_CELL) {
    return false;
  }
  if(endMatrix.x < 0 || endMatrix.x >= TOTAL_ROW_CELL ||
     endMatrix.y < 0 || endMatrix.y >= TOTAL_COLUMN_CELL) {
    return false;
  }
  NumberObject* startNumber = numberObjects[int(startMatrix.x)][int(startMatrix.y)];
  NumberObject* endNumber = numberObjects[int(endMatrix.x)][int(endMatrix.y)];
  if(startNumber == nullptr || endNumber == nullptr) {
    return false;
  } else if(startNumber != nullptr && endNumber != nullptr) {
    if(endNumber->getTraveled()) { return false; }
    return abilityConnect(startNumber, endNumber);
  } else {
    return false;
  }
}

bool GameBoard::abilityConnect(NumberObject* lhs, NumberObject* rhs) {
  if(lhs->getValue() != rhs->getValue()) { return false; }

  if(lhs->getMatrix().x == rhs->getMatrix().x) {
    
    return abs(lhs->getMatrix().y - rhs->getMatrix().y) == 1;
    
  } else if (lhs->getMatrix().y == rhs->getMatrix().y) {
    
    return abs(lhs->getMatrix().x - rhs->getMatrix().x) == 1;
    
  } else if (lhs->getMatrix().x != rhs->getMatrix().x && lhs->getMatrix().y != rhs->getMatrix().y) {

    return abs(lhs->getMatrix().x - rhs->getMatrix().x) == 1 && abs(lhs->getMatrix().y - rhs->getMatrix().y) == 1;
    
  }
  return false;
}

void GameBoard::printConnectPoints(const std::vector<Vec2>& points) {
  CCLOG("-----------------------");
  for(int i = 0; i < points.size(); i++) {
    Vec2 matrix = points[i];
    NumberObject* number = numberObjects[int(matrix.x)][int(matrix.y)];
    if(number != nullptr) {
      CCLOG("x: %d, y: %d, value = %d", int(matrix.x), int(matrix.y), number->getValue());
    } else {
      CCLOG("x: %d, y: %d, value = null", int(matrix.x), int(matrix.y));
    }
  }
  CCLOG("***********************");
}
