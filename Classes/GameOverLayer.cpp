//
//  GameOverLayer.cpp
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#include "GameOverLayer.h"
#include "GameConfig.h"
#include "ColorFactory.h"
#include "ui/CocosGUI.h"
#include "CustomButton.h"

GameOverLayer::~GameOverLayer() {
  this->delegate = nullptr;
}

void GameOverLayer::buildUI(float height, Color4B layerColor) {
  layerSize = Size(Director::getInstance()->getWinSize().width, height);
  auto backgroundColor = cocos2d::LayerColor::create(layerColor);
  backgroundColor->setContentSize(layerSize);
  this->addChild(backgroundColor);
  
  Label* label = Label::createWithTTF("GAME OVER!", FONT_NAME_NUMBER_LABEL, FONT_SIZE_GAME_OVER_LABEL);
  label->setPosition(Vec2(layerSize.width/2.0, layerSize.height/2.0));
  label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
  label->setColor(ColorFactory::GetInstance()->getTextColor());
  addChild(label);
  
  /// addEndGameButton
  addEndGameButton();
  moveDownAndAppearAnimation();
}

void GameOverLayer::addEndGameButton() {
  CustomButton* backButton = CustomButton::create(BACK_BUTTON_NAME, "", [&, this] { handleTapOnBackButton(); });
  backButton->setPosition(Vec2(64.0, layerSize.height/2.0));
  addChild(backButton);
  
  CustomButton* resetButton = CustomButton::create(RESET_BUTTON_NAME, "", [&, this] { handleTapOnResetButton(); });
  resetButton->setPosition(Vec2(layerSize.width - 64.0, backButton->getPositionY()));
  addChild(resetButton);
}

void GameOverLayer::handleTapOnBackButton() {
  if(delegate == nullptr) { return; };
  delegate->clickBackButton();
}
void GameOverLayer::handleTapOnResetButton() {
  if(delegate == nullptr) { return; };
  delegate->clickResetButton();
}

void GameOverLayer::setDelegate(EventClickButtonDelegate* delegate) {
  this->delegate = delegate;
}

void GameOverLayer::moveUpAndDisAppearAnimation(function<void()> completion) {
  auto moveToTop = MoveTo::create(GAME_OVER_MOVE_TO_DURATION, Vec2(0.0, Director::getInstance()->getWinSize().height + layerSize.height));
  auto fadeOut = FadeOut::create(GAME_OVER_MOVE_TO_DURATION);
  auto sequence = Sequence::create(moveToTop, fadeOut, nullptr);
  auto callback = CallFunc::create([&, completion](){ completion(); });
  auto sequenceWithCallback = Sequence::create(sequence, callback, nullptr);
  runAction(sequenceWithCallback);
}

void GameOverLayer::moveDownAndAppearAnimation() {
  auto moveToBottom = MoveTo::create(GAME_OVER_MOVE_TO_DURATION, Vec2(0.0, Director::getInstance()->getWinSize().height - layerSize.height));
  auto fadeOut = FadeOut::create(GAME_OVER_MOVE_TO_DURATION);
  auto sequence = Sequence::create(moveToBottom, fadeOut, nullptr);
  runAction(sequence);
}
