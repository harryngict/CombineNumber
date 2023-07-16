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

GameScene::GameScene() {}

GameScene::~GameScene() {
  gameBoard = nullptr;
  topMenuBarLayer = nullptr;
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
  
  auto backgroundColor = cocos2d::LayerColor::create(ColorFactory::GetInstance()->getBackgroundColor());
  addChild(backgroundColor);
  
  createTopMenuBarLayer();
  
  gameBoard = new GameBoard(TOTAL_ROW_CELL, TOTAL_COLUMN_CELL);
  Vec2 gameBoardPosition = Vec2((winSize.width - TOTAL_ROW_CELL * WIDTH_HEIGHT_CELL)/2.0,
                                (winSize.height - TOTAL_COLUMN_CELL * WIDTH_HEIGHT_CELL) /2.0);
  gameBoard->setDelegate(this);
  gameBoard->setPosition(gameBoardPosition);
  addChild(gameBoard);
  
  registerTouchEventHandler();
  return true;
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
  return gameBoard->handleTouchBegan(mTouch, pEvent);
}

void GameScene::handleTouchMove(Touch* mTouch, Event* pEvent) {
  return gameBoard->handleTouchMove(mTouch, pEvent);
}

void GameScene::handleTouchEnd(Touch* mTouch, Event* pEvent) {
  return gameBoard->handleTouchEnd(mTouch, pEvent);
}

void GameScene::createTopMenuBarLayer() {
  topMenuBarLayer = new TopMenuBarLayer();
  topMenuBarLayer->setPosition(Vec2(0.0, winSize.height - HEIGHT_TOP_MENU_LAYER));
  topMenuBarLayer->buildUI(HEIGHT_TOP_MENU_LAYER, 0, 2, ColorFactory::GetInstance()->getTopMenuBarLayerColor());
  topMenuBarLayer->setDelegate(this);
  addChild(topMenuBarLayer);
}

void GameScene::fireGameOverEvent() {
  if(gameOverLayer != nullptr) { return; }
  gameOverLayer = new GameOverLayer();
  gameOverLayer->setPosition(Vec2(0.0, winSize.height + HEIGHT_GAME_OVER_LAYER));
  gameOverLayer->buildUI(HEIGHT_GAME_OVER_LAYER, ColorFactory::GetInstance()->getGameOverLayerColor());
  gameOverLayer->setDelegate(this);
  topMenuBarLayer->setTouchEnabledOnLayer(false);
  addChild(gameOverLayer);
  
  /// show ads when game over
  showFullScreenAdvertisement(AD_GAME_OVER_KEY, AD_GAME_OVER_FREQUENCY);
}

void GameScene::fireEarnScore(int score) {
  if(topMenuBarLayer != nullptr) { topMenuBarLayer->updateEarnPoint(score); };
  int currentMaxEarnPoint = UserDefault::getInstance()->getIntegerForKey(KEY_HIGHEST_EARN_POINT, 0);
  if(score > currentMaxEarnPoint) { UserDefault::getInstance()->setIntegerForKey(KEY_HIGHEST_EARN_POINT, score); }
}

void GameScene::fireMaximumNumber(int maximumNumber) {
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
      this->topMenuBarLayer->resetData();
      this->topMenuBarLayer->setTouchEnabledOnLayer(true);
      this->gameBoard->resetGame();
      this->removeChild(gameOverLayer);
      this->gameOverLayer = nullptr;
    });
  } else {
    topMenuBarLayer->resetData();
    topMenuBarLayer->setTouchEnabledOnLayer(true);
    gameBoard->resetGame();
  }
  
  /// Show ads when click reset to refresh new game
  this->showFullScreenAdvertisement(AD_OPEN_GAME_KEY, AD_OPEN_GAME_FREQUENCY);
}

void GameScene::fireShowGuidePopUp(bool isShow) {
  if(isShow) {
    if(guidelinePopupLayer != nullptr) { return; }
    topMenuBarLayer->setTouchEnabledOnLayer(false);
    guidelinePopupLayer = new GuideLinePopUpLayer();
    guidelinePopupLayer->setPosition(Vec2(0.0, winSize.height + HEIGHT_GUIDE_POP_UP_LAYER));
    guidelinePopupLayer->buildUI(HEIGHT_GUIDE_POP_UP_LAYER, ColorFactory::GetInstance()->getGuideLineLayerColor());
    addChild(guidelinePopupLayer);
  } else {
    if(guidelinePopupLayer != nullptr) {
      guidelinePopupLayer->moveUpAndDisAppearAnimation([&]{ this->removeChild(guidelinePopupLayer); });
    }
  }
}

void GameScene::activeTouchTopBarMenuLayer() {
  topMenuBarLayer->setTouchEnabledOnLayer(true);
}

void GameScene::clickSuggestionButton() {
  topMenuBarLayer->setTouchEnabledOnLayer(false);
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

void GameScene::readyToShowAdvertisement() {
  AdmobManager::getInstance()->init(AD_BANNER_ID, AD_INTERSTITIAL_ID);
  AdmobManager::getInstance()->showBanner();
  showFullScreenAdvertisement(AD_OPEN_GAME_KEY, AD_OPEN_GAME_FREQUENCY);
}
