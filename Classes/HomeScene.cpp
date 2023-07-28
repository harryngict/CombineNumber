//
//  HomeScene.cpp
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#include "HomeScene.h"
#include "ColorFactory.h"
#include "GameConfig.h"
#include "GameScene.h"
#include "CustomButton.h"
#include "NativeBridge.h"

HomeScene::HomeScene() {}

HomeScene::~HomeScene() {}

Scene* HomeScene::createScene() {
  auto scene = Scene::create();
  auto layer = new HomeScene();
  layer->init();
  scene->addChild(layer);
  return scene;
}

bool HomeScene::init() {
  if (!Layer::init()) { return false; }
  winSize = Director::getInstance()->getWinSize();
  auto backgroundColor = cocos2d::LayerColor::create(ColorFactory::GetInstance()->getBackgroundColor());
  addChild(backgroundColor);
  
  CustomButton* playButton = CustomButton::create(PLAY_BUTTON_NAME, "", []{
    NativeBridge::getInstance()->playSound(CLICK_BUTTON_SOUND);
    NativeBridge::getInstance()->playHaptic();
    Director::getInstance()->replaceScene(GameScene::createScene());
  });
  
  playButton->setPosition(Vec2(winSize.width/2.0, winSize.height/2.0 + 64.0));
  addChild(playButton);
  
  Label* tileGameLabel = Label::createWithTTF(TITLE_GAME, FONT_LABEL_NAME, FONT_SIZE_TILE_GAME_LABEL);
  tileGameLabel->setPosition(Vec2(playButton->getPositionX(), playButton->getPositionY() + 120.0));
  tileGameLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
  tileGameLabel->setColor(ColorFactory::GetInstance()->getTextColor());
  addChild(tileGameLabel);
  
  Sprite* pointIcon = Sprite::create(EARN_POINT_ICON_NAME);
  pointIcon->setPosition(winSize.width/2.0 - 100, playButton->getPositionY() - 160.0);
  pointIcon->setScale(1.4);
  addChild(pointIcon);
  
  int currentMaxEarnPoint = UserDefault::getInstance()->getIntegerForKey(KEY_HIGHEST_EARN_POINT, 0);
  Label* highestEarnPointLabel = Label::createWithTTF(to_string(currentMaxEarnPoint),
                                                      FONT_LABEL_NAME,
                                                      FONT_SIZE_EARN_MAXIMUM_LABEL_IN_HOME_SCENE);
  highestEarnPointLabel->setPosition(Vec2(pointIcon->getPositionX(), pointIcon->getPositionY() - 80.0));
  highestEarnPointLabel->setColor(ColorFactory::GetInstance()->getTextColor());
  addChild(highestEarnPointLabel);
  
  Sprite* numberIcon = Sprite::create(MAXIMUM_NUMBER_ICON_NAME);
  numberIcon->setPosition(winSize.width/2.0 + 100.0, pointIcon->getPositionY());
  numberIcon->setScale(1.4);
  addChild(numberIcon);
  
  int currentHighestNumber = UserDefault::getInstance()->getIntegerForKey(KEY_HIGHEST_NUMBER, 0);
  Label* highestNumberLabel = Label::createWithTTF(to_string(currentHighestNumber),
                                                   FONT_LABEL_NAME,
                                                   FONT_SIZE_EARN_MAXIMUM_LABEL_IN_HOME_SCENE);
  highestNumberLabel->setPosition(Vec2(numberIcon->getPositionX(), numberIcon->getPositionY() - 80.0));
  highestNumberLabel->setColor(ColorFactory::GetInstance()->getTextColor());
  addChild(highestNumberLabel);
  
  return true;
}
