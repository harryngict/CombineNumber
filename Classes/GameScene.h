//  GameScene.h
//  Combine Number
//  Created by Harry Nguyen on 15/11/22.
//
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameBoard.h"
#include "GameBoardDelegate.h"
#include "GameOverLayer.h"
#include "TopMenuBarLayer.h"
#include "GuideLinePopUpLayer.h"

using namespace cocos2d;

class GameScene : public cocos2d::Layer, GameBoardDelegate, EventClickButtonDelegate {
private:
  Size winSize;
  GameBoard* gameBoard = nullptr;
  GameOverLayer* gameOverLayer = nullptr;
  TopMenuBarLayer* topMenuBarLayer = nullptr;
  GuideLinePopUpLayer* guidelinePopupLayer = nullptr;
  void createTopMenuBarLayer();
  void showFullScreenAdvertisement(const char* key, int frequency);
public:
  static Scene* createScene();
  GameScene();
  virtual ~GameScene();
  virtual bool init();
  virtual void fireGameOverEvent();
  virtual void fireEarnScore(int score);
  virtual void fireMaximumNumber(int maximumNumber);
  virtual void fireShowGuidePopUp(bool isShow);
  virtual void clickBackButton();
  virtual void clickResetButton();
  virtual void clickSuggestionButton();
  virtual void activeTouchTopBarMenuLayer();
  virtual void readyToShowAdvertisement();
  void registerTouchEventHandler();
  bool handleTouchBegan(Touch* mTouch, Event* pEvent);
  void handleTouchMove(Touch* mTouch, Event* pEvent);
  void handleTouchEnd(Touch* mTouch, Event* pEvent);
};

#endif /* GameScene_h */
