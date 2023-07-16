
//  AndroidLaunchingScene.h
//  Combine Number
//  Created by Harry Nguyen on 15/11/22.
//
//

#include "AndroidLaunchingScene.h"
#include "HomeScene.h"
#include "ColorFactory.h"
#include "GameConfig.h"

AndroidLaunchingScene::AndroidLaunchingScene() {}

AndroidLaunchingScene::~AndroidLaunchingScene() {}

Scene* AndroidLaunchingScene::createScene() {
  auto newScene = Scene::create();
  auto layer = new AndroidLaunchingScene();
  layer->init();
  newScene->addChild(layer);
  return newScene;
}

bool AndroidLaunchingScene::init(){
  if(!Layer::init()){ return false; }
  Size winSize = Director::getInstance()->getWinSize();
  LayerColor* colorLayer = LayerColor::create(ColorFactory::GetInstance()->getBackgroundColor(), winSize.width, winSize.height);
  addChild(colorLayer);
  
  Label* tileGameLabel = Label::createWithTTF(TITLE_GAME, FONT_NAME_NUMBER_LABEL, FONT_SIZE_TILE_GAME_LABEL);
  tileGameLabel->setPosition(Vec2(winSize.width/2.0, winSize.height/2.0));
  tileGameLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
  tileGameLabel->setColor(ColorFactory::GetInstance()->getTextColor());
  addChild(tileGameLabel);
  scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&AndroidLaunchingScene::update), 0.6);
  return true;
}

void AndroidLaunchingScene::update(float dt){
  Director::getInstance()->replaceScene(HomeScene::createScene());
}
