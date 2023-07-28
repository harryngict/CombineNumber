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
#include "UndoData.h"

using namespace cocos2d;

class GameBoard: public Layer {
private:
  int rows, columns, maximumNumber, earnPoint, totalNumberNeedFillUp;
  bool isTouchAvailable;
  Size size;
  stack<UndoData> stackUndoDatas;
  stack<NumberObject*> stackTouchNumbers;
  vector<DrawLineObject*> drawLines;
  NumberObject*  numberObjects[TOTAL_ROW_CELL][TOTAL_COLUMN_CELL];
  GameBoardDelegate* delegate = nullptr;
  
  bool isTouchingInsideGameBoard(const Vec2& position);
  Vec2 convertMatrixToGameBoardPosition(int row, int column);
  Vec2 convertPositionToGameBoardMatrix(const Vec2& position);
  Vec2 convertTouchToGameBoardPosition(Touch* mTouch);
  void drawFirstTimeOpenGameBoard(function<void()> completion);
  void drawNumber(int value, int row, int column, Color3B textColor, Color4F circleColor, function<void()> completion);
  NumberObject* getTouchNumberObject(int row, int column);
  
  void highLightSameNumber(NumberObject* number);
  void revertHighLightNumber();
  
  void addLineWhenMove(const Vec2& startMatrix, const Vec2& endMatrix, Color4F color);
  void removeLineWhenMove(const Vec2& startMatrix, const Vec2& endMatrix);
  void removeAllLines();
  
  bool existNumberOnTouchStacks(NumberObject* number);
  void handleTouchStackWhenTouchEnded();
  void handleConnectNumber(function<void()> completion);
  void handleDropNumber(function<void()> completion);
  void fillUpNewNumberForGameBoard(function<void()> completion);
  
  bool checkGameOver();
  bool abilityConnect(NumberObject* lhs, NumberObject* rhs);
  bool checkAbilityConnect(const Vec2& startMatrix, const Vec2& endMatrix);
  void resetTraveledNumber(vector<Vec2> points);
  void cleanAllNumberOnGameBoard();
  vector<Vec2> getAllAbilityConnectPoints();
  vector<Vec2> getAbilityConnectPointsAt(int row, int column);
  vector<Vec2> dfsCheckAbilityConnect(int row, int column, vector<Vec2>& connectPoints);
  void moveGuideSpriteToPoints(Sprite* sprite, const std::vector<Vec2>& points, function<void()> completion);
  void printConnectPoints(const std::vector<Vec2>& points);
  vector<int> getValueOfAllNumberOnGameBoard();
  void pushUndoDataBeforeGameBoardChanged();
  void clearPreTouchNumberBeforeTouchBegan();
  void removeOneNumberAt(int row, int column, function<void()> completion);
  void dropAndFillUpNumber(function<void()> completion);
public:
  GameBoard(int rows, int columns);
  virtual ~GameBoard();
  bool handleTouchBeganWhenRemoveNumber(Touch* mTouch, Event* pEvent, function<void(bool)> completion);
  bool handleTouchBegan(Touch* mTouch, Event* pEvent);
  void handleTouchMove(Touch* mTouch, Event* pEvent);
  void handleTouchEnd(Touch* mTouch, Event* pEvent);
  void setDelegate(GameBoardDelegate* delegate);
  void resetGameBoard();
  void showGuideLineLayer(int status);
  void activateUndoGameBoard(function<void(bool)> completion);
  int getEarnPoint() { return earnPoint; };
  int getMaximumNumber() { return maximumNumber; };
};

#endif /* GameBoard_h */
