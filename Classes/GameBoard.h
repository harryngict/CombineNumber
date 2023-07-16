//
//  GameBoard.h
//  Combine Number
//
//  Created by Harry Nguyen on 12/7/23.
//

#ifndef GameBoard_h
#define GameBoard_h
#include <stack>
#include "cocos2d.h"
#include "NumberObject.h"
#include "GameConfig.h"
#include "DrawLineObject.h"
#include "GameBoardDelegate.h"

using namespace cocos2d;

class GameBoard: public Layer {
private:
  int rows, columns, maximumNumber, earnPoint, totalNumberNeedFillUp;
  bool isTouchAvailable;
  Size size;
  stack<NumberObject*> stackTouchNumbers;
  vector<DrawLineObject*> drawLines;
  NumberObject*  numberObjects[TOTAL_ROW_CELL][TOTAL_COLUMN_CELL];
  GameBoardDelegate* delegate = nullptr;
  
  bool isTouchingInsideGameBoard(const Vec2& position);
  Vec2 convertMatrixToGameBoardPosition(int row, int column);
  Vec2 convertPositionToGameBoardMatrix(const Vec2& position);
  Vec2 convertTouchToGameBoardPosition(Touch* mTouch);
  void drawFirstGameBoard();
  void drawNumber(int value, int row, int column, Color3B textColor, Color4F circleColor, function<void()> completion);
  NumberObject* getTouchNumberObject(int row, int column);
  
  void highLightSameNumber(NumberObject* number);
  void revertHighLightNumber();
  
  void addLineWhenMove(const Vec2& startMatrix, const Vec2& endMatrix);
  void removeLineWhenMove(const Vec2& startMatrix, const Vec2& endMatrix);
  void removeAllLines();
  
  bool existNumberOnStacks(NumberObject* number);
  void handleTouchStackWhenTouchEnded();
  void handleConnectNumber(function<void()> completion);
  void handleDropNumber();
  void fillUpGameBoard();
  
  bool checkGameOver();
  bool abilityConnect(NumberObject* lhs, NumberObject* rhs);
  bool checkAbilityConnect(const Vec2& startMatrix, const Vec2& endMatrix);
  void resetTraveledNumber(vector<Vec2> points);
  void cleanNumbers();
  vector<Vec2> getAllAbilityConnectPoints();
  vector<Vec2> getAbilityConnectPointsAt(int row, int column);
  vector<Vec2> dfsCheckAbilityConnect(int row, int column, vector<Vec2>& connectPoints);
  void moveGuideSpriteToPoints(Sprite* sprite, const std::vector<Vec2>& points, float duration, function<void()> completion);
  void printConnectPoints(const std::vector<Vec2>& points);
  vector<int> getAllAvailableNumberOnGameBoard();
public:
  GameBoard(int rows, int columns);
  virtual ~GameBoard();
  bool handleTouchBegan(Touch* mTouch, Event* pEvent);
  void handleTouchMove(Touch* mTouch, Event* pEvent);
  void handleTouchEnd(Touch* mTouch, Event* pEvent);
  void setDelegate(GameBoardDelegate* delegate);
  void resetGame();
  int getEarnPoint() { return earnPoint; };
  int getMaximumNumber() { return maximumNumber; };
  void showGuideLineLayer(int status);
};

#endif /* GameBoard_h */
