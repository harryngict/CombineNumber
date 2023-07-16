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
#include "BottomMenuBarLayer.h"

using namespace cocos2d;

class GameScene : public cocos2d::Layer, GameBoardDelegate, EventClickButtonDelegate {
private:
  bool isRemoveNumberMode;
  Size winSize;
  GameBoard* gameBoard = nullptr;
  GameOverLayer* gameOverLayer = nullptr;
  TopMenuBarLayer* topMenuBarLayer = nullptr;
  BottomMenuBarLayer* bottomMenuBarLayer = nullptr;
  GuideLinePopUpLayer* guidelinePopupLayer = nullptr;
  Label* messageLabel = nullptr;
  LayerColor* backgroundColor = nullptr;
  function<void(bool)> removeNumberCompletion;
  void createTopMenuBarLayer();
  void createBottomMenuBarLayer();
  void createMessageLabel();
  void showFullScreenAdvertisement(const char* key, int frequency);
  void setTouchEnabledOnMenuBarLayer(bool isEnabled);
  void setDataMenuBarLayer();
public:
  static Scene* createScene();
  GameScene();
  virtual ~GameScene();
  virtual bool init();
  void update(float dt);
  virtual void fireGameOverEvent();
  virtual void fireEarnScoreAndMaximumNumber(int score, int maximumNumber);
  virtual void fireShowGuidePopUp(bool isShow);
  virtual void clickBackButton();
  virtual void clickResetButton();
  virtual void clickSuggestionButton();
  virtual void clickUndoButton(function<void (bool)> completion);
  virtual void clickRemoveNumberButton(function<void(bool)> completion);
  virtual void activeTouchTopBarMenuLayer();
  virtual void readyToShowAdvertisement();
  virtual void updateMessageLabel(const string& message, bool isHiddenAfterAnimation);
  virtual void showReachToLitmitedUndoMessage(const string& message);
  void registerTouchEventHandler();
  bool handleTouchBegan(Touch* mTouch, Event* pEvent);
  void handleTouchMove(Touch* mTouch, Event* pEvent);
  void handleTouchEnd(Touch* mTouch, Event* pEvent);
};

#endif /* GameScene_h */
