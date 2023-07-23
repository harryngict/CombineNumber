//  GameScene.cpp
//  Combine Number
//  Created by Harry Nguyen on 15/11/22.
//
//

#include "GameScene.h"
#include "GameConfig.h"
#include "ColorFactory.h"
#include "HomeScene.h"
#include "AdmobManager.h"

GameScene::GameScene() {
  isRemoveNumberMode = false;
}

GameScene::~GameScene() {
  unscheduleUpdate();
  backgroundColor = nullptr;
  removeNumberCompletion = nullptr;
  gameBoard = nullptr;
  topMenuBarLayer = nullptr;
  bottomMenuBarLayer = nullptr;
  gameOverLayer = nullptr;
  guidelinePopupLayer = nullptr;
}

Scene* GameScene::createScene() {
  auto scene = Scene::create();
  auto layer = new GameScene();
  layer->init();
  scene->addChild(layer);
  return scene;
}

bool GameScene::init() {
  if (!Layer::init()) { return false; }
  winSize = Director::getInstance()->getWinSize();
  
  backgroundColor = cocos2d::LayerColor::create(ColorFactory::GetInstance()->getBackgroundColor());
  backgroundColor->setContentSize(winSize);
  addChild(backgroundColor);
  
  auto bottomBackgroundColor = cocos2d::LayerColor::create(ColorFactory::GetInstance()->getTopMenuBarLayerColor());
  bottomBackgroundColor->setContentSize(Size(winSize.width, HEIGHT_BOTTOM_POP_UP_LAYER));
  bottomBackgroundColor->setPosition(Vec2::ZERO);
  addChild(bottomBackgroundColor);
  
  createTopMenuBarLayer();
  createBottomMenuBarLayer();
  createMessageLabel();
  
  gameBoard = new GameBoard(TOTAL_ROW_CELL, TOTAL_COLUMN_CELL);
  Vec2 gameBoardPosition = Vec2((winSize.width - TOTAL_ROW_CELL * WIDTH_HEIGHT_CELL)/2.0,
                                (winSize.height - TOTAL_COLUMN_CELL * WIDTH_HEIGHT_CELL) /2.0);
  gameBoard->setDelegate(this);
  gameBoard->setPosition(gameBoardPosition);
  addChild(gameBoard);
  
  registerTouchEventHandler();
  scheduleUpdate();
  return true;
}

void GameScene::createMessageLabel() {
  messageLabel = Label::createWithTTF("", FONT_LABEL_NAME, FONT_SIZE_WARNING_LABEL);
  messageLabel->setPosition(Vec2(winSize.width/2.0, topMenuBarLayer->getPositionY() - messageLabel->getContentSize().height - 64.0));
  messageLabel->setAnchorPoint(Vec2(Vec2::ANCHOR_MIDDLE));
  messageLabel->setColor(ColorFactory::GetInstance()->getWarningMessageColor());
  messageLabel->setVisible(false);
  addChild(messageLabel);
}

void GameScene::registerTouchEventHandler() {
  auto lister = EventListenerTouchOneByOne::create();
  lister->setSwallowTouches(true);
  lister->onTouchBegan = CC_CALLBACK_2(GameScene::handleTouchBegan, this);
  lister->onTouchMoved = CC_CALLBACK_2(GameScene::handleTouchMove, this);
  lister->onTouchEnded = CC_CALLBACK_2(GameScene::handleTouchEnd, this);
  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lister, this);
}

bool GameScene::handleTouchBegan(Touch* mTouch, Event* pEvent) {
  if(isRemoveNumberMode) {
    return gameBoard->handleTouchBeganWhenRemoveNumber(mTouch, pEvent, [&, this](bool isCompleted){
      this->isRemoveNumberMode = false;
      this->backgroundColor->setColor(Color3B(ColorFactory::GetInstance()->getBackgroundColor().r,
                                              ColorFactory::GetInstance()->getBackgroundColor().g,
                                              ColorFactory::GetInstance()->getBackgroundColor().b));
      this->messageLabel->setVisible(false);
      this->setTouchEnabledOnMenuBarLayer(true);
      this->removeNumberCompletion(isCompleted);
    });
  } else {
    return gameBoard->handleTouchBegan(mTouch, pEvent);
  }
}

void GameScene::handleTouchMove(Touch* mTouch, Event* pEvent) {
  if(isRemoveNumberMode) { return; }
  gameBoard->handleTouchMove(mTouch, pEvent);
}

void GameScene::handleTouchEnd(Touch* mTouch, Event* pEvent) {
  if(isRemoveNumberMode) { return; }
  gameBoard->handleTouchEnd(mTouch, pEvent);
}

void GameScene::createTopMenuBarLayer() {
  topMenuBarLayer = new TopMenuBarLayer();
  topMenuBarLayer->setPosition(Vec2(0.0, winSize.height - HEIGHT_TOP_POP_UP_LAYER));
  topMenuBarLayer->buildUI(HEIGHT_TOP_POP_UP_LAYER, 0, 2, ColorFactory::GetInstance()->getTopMenuBarLayerColor());
  topMenuBarLayer->setDelegate(this);
  addChild(topMenuBarLayer);
}

void GameScene::createBottomMenuBarLayer() {
  bottomMenuBarLayer = new BottomMenuBarLayer();
  bottomMenuBarLayer->setPosition(Vec2::ZERO);
  bottomMenuBarLayer->buildUI(HEIGHT_BOTTOM_POP_UP_LAYER, ColorFactory::GetInstance()->getTopMenuBarLayerColor());
  bottomMenuBarLayer->setDelegate(this);
  addChild(bottomMenuBarLayer);
}

void GameScene::fireGameOverEvent() {
  if(gameOverLayer != nullptr) { return; }
  gameOverLayer = new GameOverLayer();
  gameOverLayer->setPosition(Vec2(0.0, winSize.height + HEIGHT_TOP_POP_UP_LAYER));
  gameOverLayer->buildUI(HEIGHT_TOP_POP_UP_LAYER, ColorFactory::GetInstance()->getGameOverLayerColor());
  gameOverLayer->setDelegate(this);
  setTouchEnabledOnMenuBarLayer(false);
  addChild(gameOverLayer);
  
  showFullScreenAdvertisement(AD_GAME_OVER_KEY, AD_GAME_OVER_FREQUENCY);
}

void GameScene::fireEarnScoreAndMaximumNumber(int score, int maximumNumber) {
  if(topMenuBarLayer != nullptr) { topMenuBarLayer->updateEarnPoint(score); };
  int currentMaxEarnPoint = UserDefault::getInstance()->getIntegerForKey(KEY_HIGHEST_EARN_POINT, 0);
  if(score > currentMaxEarnPoint) { UserDefault::getInstance()->setIntegerForKey(KEY_HIGHEST_EARN_POINT, score); }
  
  if(topMenuBarLayer != nullptr) { topMenuBarLayer->updateMaximumNumber(maximumNumber); };
  int currentMaximumNumber = UserDefault::getInstance()->getIntegerForKey(KEY_HIGHEST_NUMBER, 0);
  if(maximumNumber > currentMaximumNumber) { UserDefault::getInstance()->setIntegerForKey(KEY_HIGHEST_NUMBER, maximumNumber); }
}

void GameScene::clickBackButton() {
  Director::getInstance()->replaceScene(HomeScene::createScene());
}

void GameScene::clickResetButton() {
  if(gameOverLayer != nullptr) {
    gameOverLayer->moveUpAndDisAppearAnimation([&] {
      this->setDataMenuBarLayer();
      this->setTouchEnabledOnMenuBarLayer(true);
      this->gameBoard->resetGameBoard();
      this->removeChild(gameOverLayer);
      this->gameOverLayer = nullptr;
    });
  } else {
    setDataMenuBarLayer();
    setTouchEnabledOnMenuBarLayer(true);
    gameBoard->resetGameBoard();
  }
  
  /// Show ads when click reset to refresh new game
  this->showFullScreenAdvertisement(AD_OPEN_GAME_KEY, AD_OPEN_GAME_FREQUENCY);
}

void GameScene::fireShowGuidePopUp(bool isShow) {
  if(isShow) {
    if(guidelinePopupLayer != nullptr) { return; }
    setTouchEnabledOnMenuBarLayer(false);
    guidelinePopupLayer = new GuideLinePopUpLayer();
    guidelinePopupLayer->setPosition(Vec2(0.0, winSize.height + HEIGHT_TOP_POP_UP_LAYER));
    guidelinePopupLayer->buildUI(HEIGHT_TOP_POP_UP_LAYER, ColorFactory::GetInstance()->getGuideLineLayerColor());
    addChild(guidelinePopupLayer);
  } else {
    if(guidelinePopupLayer != nullptr) {
      guidelinePopupLayer->moveUpAndDisAppearAnimation([&]{ this->removeChild(guidelinePopupLayer); });
    }
  }
}

void GameScene::activeTouchTopBarMenuLayer() {
  setTouchEnabledOnMenuBarLayer(true);
}

void GameScene::clickSuggestionButton() {
  setTouchEnabledOnMenuBarLayer(false);
  gameBoard->showGuideLineLayer(CLICK_SUGGESTION);
}

void GameScene::showFullScreenAdvertisement(const char* key, int frequency) {
  int currentCount = UserDefault::getInstance()->getIntegerForKey(key, 0);
  if(currentCount == frequency) {
    AdmobManager::getInstance()->showInterstitial([](bool result) { });
    UserDefault::getInstance()->setIntegerForKey(key, 0);
  } else {
    UserDefault::getInstance()->setIntegerForKey(key, currentCount + 1);
  }
}

void GameScene::clickUndoButton(function<void (bool)> completion) {
  gameBoard->activateUndoGameBoard(completion);
}

void GameScene::update(float dt) {
  if(bottomMenuBarLayer == nullptr) { return; }
  bool isBannerViewVisible = AdmobManager::getInstance()->isBannerViewVisible();
  bottomMenuBarLayer->setPositionY(isBannerViewVisible ? bottomMenuBarLayer->getContentSize().height/2.0 : 0.0);
}

void GameScene::setTouchEnabledOnMenuBarLayer(bool isEnabled) {
  topMenuBarLayer->setTouchEnabledOnLayer(isEnabled);
  bottomMenuBarLayer->setTouchEnabledOnLayer(isEnabled);
}

void GameScene::setDataMenuBarLayer() {
  bottomMenuBarLayer->resetData();
  topMenuBarLayer->resetData();
}

void GameScene::readyToShowAdvertisement() {
  AdmobManager::getInstance()->init(AD_BANNER_ID, AD_INTERSTITIAL_ID);
  AdmobManager::getInstance()->showBanner();
  showFullScreenAdvertisement(AD_OPEN_GAME_KEY, AD_OPEN_GAME_FREQUENCY);
}

void GameScene::updateMessageLabel(const string& message, bool isHiddenAfterAnimation) {
  messageLabel->setVisible(true);
  messageLabel->setString(message);
    messageLabel->stopAllActions();
  auto scaleUp = ScaleTo::create(TIME_RUN_MESSAGE_LABEL_ANIMATION, 1.26f);
  auto scaleDown = ScaleTo::create(TIME_RUN_MESSAGE_LABEL_ANIMATION, 1.0f);
  if(isHiddenAfterAnimation) {
    auto delay = DelayTime::create(DELAY_WARNING_LABEL_DISAPPEAR);
    auto completionCallFunc = CallFunc::create([&, this]() { this->messageLabel->setVisible(false); });
    auto sequence = Sequence::create(scaleUp, scaleDown, delay, completionCallFunc, nullptr);
    messageLabel->runAction(sequence);
  } else {
    auto sequence = Sequence::create(scaleUp, scaleDown, nullptr);
    messageLabel->runAction(sequence);
  }
}

void GameScene::showReachToLitmitedUndoMessage(const string& message) {
  this->updateMessageLabel(message, true);
}

void GameScene::clickRemoveNumberButton(function<void(bool)> completion) {
  isRemoveNumberMode  = true;
  removeNumberCompletion  = completion;
  setTouchEnabledOnMenuBarLayer(false);
  updateMessageLabel(EDIT_NUMBER_MESSAGE, false);
  backgroundColor->setColor(ColorFactory::GetInstance()->getBackgroundColorWhenRemoveMode());
}
