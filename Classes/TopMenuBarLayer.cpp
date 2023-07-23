//
//  TopMenuBarLayer.cpp
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#include "TopMenuBarLayer.h"
#include "GameConfig.h"
#include "ColorFactory.h"
#include "SoundManager.h"

TopMenuBarLayer::TopMenuBarLayer() {
  currentPoint = 0;
  currentMaximumNumber = 2;
}

TopMenuBarLayer::~TopMenuBarLayer(){
  this->delegate = nullptr;
}

void TopMenuBarLayer::buildUI(float height,
                              int earnPoint,
                              int maximumNumber,
                              Color4B layerColor) {
  layerSize = Size(Director::getInstance()->getWinSize().width, height);
  auto backgroundColor = cocos2d::LayerColor::create(layerColor);
  backgroundColor->setContentSize(layerSize);
  addChild(backgroundColor);
  
  backButton = CustomButton::create(BACK_BUTTON_NAME, "", [&, this] { handleTapOnBackButton(); });
  backButton->setPosition(Vec2(layerSize.width - 48.0, layerSize.height/2.0));
  addChild(backButton);
  
  resetButton = CustomButton::create(RESET_BUTTON_NAME, "", [&, this] { handleTapOnResetButton(); });
  resetButton->setPosition(Vec2(backButton->getPositionX() - 80.0, backButton->getPositionY()));
  addChild(resetButton);
  
  Sprite* maximumNumberIcon = Sprite::create(MAXIMUM_NUMBER_ICON_NAME);
  maximumNumberIcon->setPosition(48.0, resetButton->getPositionY());
  addChild(maximumNumberIcon);
  
  maximumNumberLabel = Label::createWithTTF(to_string(maximumNumber), FONT_LABEL_NAME, FONT_SIZE_EARN_MAXIMUM_LABEL_IN_GAME_SCENE);
  maximumNumberLabel->setPosition(Vec2(maximumNumberIcon->getPositionX() + maximumNumberIcon->getContentSize().width*0.5,
                                       maximumNumberIcon->getPositionY() - maximumNumberLabel->getContentSize().height/8.0));
  maximumNumberLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  maximumNumberLabel->setColor(ColorFactory::GetInstance()->getTextColor());
  addChild(maximumNumberLabel);
  
  Sprite* earnPointIcon = Sprite::create(EARN_POINT_ICON_NAME);
  earnPointIcon->setPosition(maximumNumberLabel->getPositionX() + maximumNumberLabel->getContentSize().width + 48.0,
                             resetButton->getPositionY());
  addChild(earnPointIcon);
  
  scoreLabel = Label::createWithTTF(to_string(earnPoint), FONT_LABEL_NAME, FONT_SIZE_EARN_MAXIMUM_LABEL_IN_GAME_SCENE);
  scoreLabel->setPosition(Vec2(earnPointIcon->getPositionX() + earnPointIcon->getContentSize().width*0.5 + 4.0,
                               earnPointIcon->getPositionY() - scoreLabel->getContentSize().height/8.0));
  scoreLabel->setAnchorPoint(Vec2(Vec2::ANCHOR_MIDDLE_LEFT));
  scoreLabel->setColor(ColorFactory::GetInstance()->getTextColor());
  addChild(scoreLabel);
}

void TopMenuBarLayer::setDelegate(EventClickButtonDelegate* delegate) {
  this->delegate = delegate;
}

void TopMenuBarLayer::handleTapOnBackButton() {
  if(delegate == nullptr) { return; };
  SoundManager::getInstance()->playSound(CLICK_BUTTON_SOUND);
  SoundManager::getInstance()->playHaptic();
  delegate->clickBackButton();
}

void TopMenuBarLayer::handleTapOnResetButton() {
  if(delegate == nullptr) { return; };
  SoundManager::getInstance()->playSound(CLICK_BUTTON_SOUND);
  SoundManager::getInstance()->playHaptic();
  delegate->clickResetButton();
}

void TopMenuBarLayer::updateEarnPoint(int point) {
  if(point == currentPoint) { return; }
  scoreLabel->setString(to_string(point));
  scoreLabel->runAction(createLabelAnimation());
  currentPoint = point;
}

void TopMenuBarLayer::updateMaximumNumber(int number) {
  if(number == currentMaximumNumber) { return; }
  maximumNumberLabel->setString(to_string(number));
  maximumNumberLabel->runAction(createLabelAnimation());
  currentMaximumNumber = number;
}

void TopMenuBarLayer::setTouchEnabledOnLayer(bool isEnabled) {
  backButton->setTouchEnabled(isEnabled);
  resetButton->setTouchEnabled(isEnabled);
}

Sequence* TopMenuBarLayer::createLabelAnimation() {
  auto scaleUp = ScaleTo::create(TIME_RUN_ANIMATION, 2.0f);
  auto scaleDown = ScaleTo::create(TIME_RUN_ANIMATION, 1.0f);
  auto sequence = Sequence::create(scaleUp, scaleDown, nullptr);
  return sequence;
}

void TopMenuBarLayer::resetData() {
  currentPoint = 0;
  currentMaximumNumber = 2;

  scoreLabel->setString(to_string(currentPoint));
  maximumNumberLabel->setString(to_string(currentMaximumNumber));
}
