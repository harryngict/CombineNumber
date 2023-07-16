//
//  NumberObject.cpp
//  Combine Number
//
//  Created by Harry Nguyen on 12/7/23.
//

#include "NumberObject.h"
#include "GameConfig.h"

NumberObject::NumberObject(int value, const Vec2& matrix, Color3B textColor, Color4F circleColor) {
  this->value = value;
  this->matrix = matrix;
  this->circleColor = circleColor;
  
  shadowNode = DrawNode::create();
  addChild(shadowNode);
  circleNode = DrawNode::create();
  addChild(circleNode);

  drawCircleColorWithShadow(circleColor);
  
  numberLabel = Label::createWithTTF(to_string(value), FONT_LABEL_NAME, FONT_SIZE_NUMBER_LABEL);
  numberLabel->setPosition(Vec2(WIDTH_HEIGHT_CELL/2.0, WIDTH_HEIGHT_CELL/2.0));
  numberLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
  numberLabel->setColor(textColor);
  addChild(numberLabel);
  
  animationStatus = IDLE;
  isMovingUp = false;
  isTraveled = false;
  scheduleUpdate();
}

void NumberObject::setPosition(const Vec2& pos) {
  this->originPosition = pos;
  Node::setPosition(pos);
}

NumberObject::~NumberObject() {
  unscheduleUpdate();
  circleNode = nullptr;
  shadowNode = nullptr;
  numberLabel = nullptr;
}

void NumberObject::drawCircleColorWithShadow(Color4F color) {
  Vec2 center = Vec2(WIDTH_HEIGHT_CELL/2.0, WIDTH_HEIGHT_CELL/2.0);
  float radius =  (WIDTH_HEIGHT_CELL/2.0 - CIRCLE_RADIUS);
  float numSegments = 100.0;
  circleNode->drawSolidCircle(center, radius, 0.0f, numSegments, color);
  
  Color4F shadowColor(0.0f, 0.0f, 0.0f, 0.16f);
  Vec2 shadowCenter = Vec2((WIDTH_HEIGHT_CELL - 18.0)/2.0, (WIDTH_HEIGHT_CELL - 8.0)/2.0);
  shadowNode->drawSolidCircle(shadowCenter, radius, 0.0f, numSegments, shadowColor);
}

void NumberObject::setActiveNumber(bool isActive) {
  shadowNode->setVisible(isActive);
  circleNode->setOpacity(isActive ? 255 : NUMBER_DISABLE_OPACITY);
  numberLabel->setOpacity(isActive ? 255 : NUMBER_DISABLE_OPACITY);
}

void NumberObject::setAnimationStatus(int animationStatus) {
  this->animationStatus = animationStatus;
}

void NumberObject::setMatrix(const Vec2& matrix) {
  this->matrix = matrix;
}

void NumberObject::setTraveled(bool isTraveled) {
  this->isTraveled = isTraveled;
}

void NumberObject::runIncreaseNumberAnimation(int newValue, Color3B newTextColor, Color4F newCircleColor, function<void()> completion) {
  auto scaleUp = ScaleTo::create(TIME_RUN_ANIMATION, 3.0f);
  auto scaleDown = ScaleTo::create(TIME_RUN_ANIMATION, 1.0f);
  auto updateText = CallFunc::create([&, this, newValue, newTextColor, newCircleColor, completion]() {
    circleColor = newCircleColor;
    value = newValue;
    numberLabel->setString(to_string(value));
    numberLabel->setColor(newTextColor);
    shadowNode->clear();
    circleNode->clear();
    drawCircleColorWithShadow(newCircleColor);
  });
  
  auto delay = DelayTime::create(DELAY_DROP_NUMBER);
  
  auto completionCallFunc = CallFunc::create([&, this,completion]() {
    animationStatus = REVERT_ANIMATION_AFTER_TOUCH;
    completion();
  });
  
  auto sequence = Sequence::create(scaleUp, updateText, scaleDown, delay, completionCallFunc, nullptr);
  numberLabel->runAction(sequence);
}

void NumberObject::runMoveToAndAppearAnimation(const Vec2& source, const Vec2& destination, function<void()> completion) {
  auto moveTo = createMoveToAnimation(source, destination);
  auto callFunc = CallFunc::create([&, this, destination, completion]() {
    this->setPosition(destination);
    completion();
  });
  
  auto sequence = Sequence::create(moveTo, callFunc, nullptr);
  this->runAction(sequence);
}

void NumberObject::runMoveToAndDisAppearAnimation(const Vec2& source, const Vec2& destination,  function<void()> completion) {
  auto moveTo = createMoveToAnimation(source, destination);
  auto hide = Hide::create();
  auto callFunc = CallFunc::create([&, this, destination, completion]() {
    this->setPosition(destination);
    completion();
  });
  auto sequence = Sequence::create(moveTo, hide, callFunc, nullptr);
  this->runAction(sequence);
}

EaseSineInOut* NumberObject::createMoveToAnimation(const Vec2& source, const Vec2& destination) {
  Vec2 deltaPosition = destination - source;
  float speed = DROP_DOWN_ANIMATION_SPEED;
  float distance = deltaPosition.length();
  float duration = distance / speed;
  auto moveBy = MoveBy::create(duration, deltaPosition);
  return EaseSineInOut::create(moveBy);
}

void NumberObject::update(float dt) {
  switch (animationStatus) {
    case IDLE: break;
      
    case REVERT_ANIMATION_AFTER_TOUCH:
      this->setPositionY(originPosition.y);
      break;
      
    case TOUCH_ANIMATION:
      float speed = TOUCH_ANIMATION_SPEED;
      float deltaY = speed * dt * (isMovingUp ? 1 : -1);
      float currentYPosition = this->getPositionY();
      currentYPosition += deltaY;
      this->setPositionY(currentYPosition);
      if (currentYPosition >= originPosition.y + TOUCH_ANIMATION_DELTA && isMovingUp) {
        isMovingUp = false;
      } else if (currentYPosition <= originPosition.y - TOUCH_ANIMATION_DELTA && !isMovingUp) {
        isMovingUp = true;
      }
      break;
  }
}
