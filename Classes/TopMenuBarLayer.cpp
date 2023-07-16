//
//  TopMenuBarLayer.cpp
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#include "TopMenuBarLayer.h"
#include "GameConfig.h"
#include "ColorFactory.h"

TopMenuBarLayer::TopMenuBarLayer() {
  currentSuggestionCount = DEFAULT_SUGGESTION_TIME;
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
  backButton->setPosition(Vec2(layerSize.width - 64.0, layerSize.height/2.0));
  addChild(backButton);
  
  suggestionButton = CustomButton::create(LIGHT_ON_BUTTON_NAME, "", currentSuggestionCount, [&, this]{ handleTapOnSuggestionButton(); });
  suggestionButton->setPosition(Vec2(backButton->getPositionX() - 84.0, backButton->getPositionY() + 8.0));
  addChild(suggestionButton);
  
  resetButton = CustomButton::create(RESET_BUTTON_NAME, "", [&, this] { handleTapOnResetButton(); });
  resetButton->setPosition(Vec2(suggestionButton->getPositionX() - 84.0, backButton->getPositionY()));
  addChild(resetButton);
  
  Sprite* maximumNumberIcon = Sprite::create(MAXIMUM_NUMBER_ICON_NAME);
  maximumNumberIcon->setPosition(64.0, resetButton->getPositionY());
  addChild(maximumNumberIcon);
  
  maximumNumberLabel = Label::createWithTTF(to_string(maximumNumber), FONT_NAME_NUMBER_LABEL, FONT_SIZE_EARN_MAXIMUM_LABEL_IN_GAME_SCENE);
  maximumNumberLabel->setPosition(Vec2(maximumNumberIcon->getPositionX() + maximumNumberIcon->getContentSize().width*0.6,
                                       maximumNumberIcon->getPositionY() - maximumNumberLabel->getContentSize().height/8.0));
  maximumNumberLabel->setAnchorPoint(Vec2(0.0, 0.5));
  maximumNumberLabel->setColor(ColorFactory::GetInstance()->getTextColor());
  addChild(maximumNumberLabel);
  
  Sprite* earnPointIcon = Sprite::create(EARN_POINT_ICON_NAME);
  earnPointIcon->setPosition(maximumNumberLabel->getPositionX() + maximumNumberLabel->getContentSize().width + 72.0,
                             resetButton->getPositionY());
  addChild(earnPointIcon);
  
  scoreLabel = Label::createWithTTF(to_string(earnPoint), FONT_NAME_NUMBER_LABEL, FONT_SIZE_EARN_MAXIMUM_LABEL_IN_GAME_SCENE);
  scoreLabel->setPosition(Vec2(earnPointIcon->getPositionX() + earnPointIcon->getContentSize().width*0.6,
                               earnPointIcon->getPositionY() - scoreLabel->getContentSize().height/8.0));
  scoreLabel->setAnchorPoint(Vec2(0.0, 0.5));
  scoreLabel->setColor(ColorFactory::GetInstance()->getTextColor());
  addChild(scoreLabel);
}

void TopMenuBarLayer::setDelegate(EventClickButtonDelegate* delegate) {
  this->delegate = delegate;
}

void TopMenuBarLayer::handleTapOnBackButton() {
  if(delegate == nullptr) { return; };
  delegate->clickBackButton();
}

void TopMenuBarLayer::handleTapOnResetButton() {
  if(delegate == nullptr) { return; };
  delegate->clickResetButton();
}

void TopMenuBarLayer::handleTapOnSuggestionButton() {
  if(delegate == nullptr) { return; };
  if(currentSuggestionCount <= 0) { return;};
  currentSuggestionCount -= 1;
  suggestionButton->setLabelVisibility(currentSuggestionCount > 0);
  suggestionButton->updateText(currentSuggestionCount);
  delegate->clickSuggestionButton();
  if(currentSuggestionCount == 0) { suggestionButton->loadTextureNormal(LIGHT_OFF_BUTTON_NAME, cocos2d::ui::Button::TextureResType::LOCAL); }
}

void TopMenuBarLayer::updateEarnPoint(int point) {
  if(point <= currentPoint) { return; }
  currentPoint = point;
  scoreLabel->setString(to_string(point));
  scoreLabel->runAction(createLabelAnimation());
}

void TopMenuBarLayer::updateMaximumNumber(int number) {
  if(number <= currentMaximumNumber) { return; }
  currentMaximumNumber = number;
  maximumNumberLabel->setString(to_string(number));
  maximumNumberLabel->runAction(createLabelAnimation());
}

void TopMenuBarLayer::setTouchEnabledOnLayer(bool isEnabled) {
  backButton->setTouchEnabled(isEnabled);
  resetButton->setTouchEnabled(isEnabled);
  suggestionButton->setTouchEnabled(isEnabled);
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
  currentSuggestionCount = DEFAULT_SUGGESTION_TIME;
  scoreLabel->setString(to_string(currentPoint));
  maximumNumberLabel->setString(to_string(currentMaximumNumber));
  suggestionButton->updateText(currentSuggestionCount);
}
