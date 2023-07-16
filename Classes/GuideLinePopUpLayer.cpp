//
//  GuideLinePopUpLayer.cpp
//  Combine Number
//
//  Created by Harry Nguyen on 15/7/23.
//

#include "GuideLinePopUpLayer.h"
#include "GameConfig.h"
#include "ColorFactory.h"

GuideLinePopUpLayer::~GuideLinePopUpLayer() {}

void GuideLinePopUpLayer::buildUI(float height, Color4B layerColor) {
  layerSize = Size(Director::getInstance()->getWinSize().width, height);
  auto backgroundColor = cocos2d::LayerColor::create(layerColor);
  backgroundColor->setContentSize(layerSize);
  addChild(backgroundColor);
  moveDownAndAppearAnimation();
  
  Label* titleLabel = Label::createWithTTF(GUIDE_TITLE_TEXT, FONT_LABEL_NAME, FONT_SIZE_GUIDE_LABEL);
  titleLabel->setPosition(Vec2(layerSize.width/2.0, layerSize.height/2.0));
  titleLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
  titleLabel->setColor(ColorFactory::GetInstance()->getTextColor());
  addChild(titleLabel);
  
  Label* subTitleLabel = Label::createWithTTF(GUIDE_SUB_TITLE_TEXT, FONT_LABEL_NAME, FONT_SIZE_GUIDE_LABEL);
  subTitleLabel->setPosition(Vec2(titleLabel->getPositionX(), layerSize.height/2.0 - 40.0));
  subTitleLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
  subTitleLabel->setColor(ColorFactory::GetInstance()->getTextColor());
  addChild(subTitleLabel);
}

void GuideLinePopUpLayer::moveUpAndDisAppearAnimation(function<void()> completion) {
  auto moveToTop = MoveTo::create(GAME_OVER_MOVE_TO_DURATION, Vec2(0.0, Director::getInstance()->getWinSize().height + layerSize.height));
  auto fadeOut = FadeOut::create(GAME_OVER_MOVE_TO_DURATION);
  auto sequence = Sequence::create(moveToTop, fadeOut, nullptr);
  auto callback = CallFunc::create([&, completion](){ completion(); });
  auto sequenceWithCallback = Sequence::create(sequence, callback, nullptr);
  runAction(sequenceWithCallback);
}

void GuideLinePopUpLayer::moveDownAndAppearAnimation() {
  auto moveToBottom = MoveTo::create(GAME_OVER_MOVE_TO_DURATION, Vec2(0.0, Director::getInstance()->getWinSize().height - layerSize.height));
  auto fadeOut = FadeOut::create(GAME_OVER_MOVE_TO_DURATION);
  auto sequence = Sequence::create(moveToBottom, fadeOut, nullptr);
  runAction(sequence);
}
