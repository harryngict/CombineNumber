//
//  BottomMenuBarLayer.cpp
//  CombineNumber
//
//  Created by Hoang Nguyen on 21/7/23.
//

#include "BottomMenuBarLayer.h"
#include "SoundManager.h"

BottomMenuBarLayer::BottomMenuBarLayer() {
  suggestCount = DEFAULT_SUGGESTION_TIME;
  undoCount = DEFAULT_UNDO_TIME;
  removeNumberCount = DEFAULT_REMOVE_NUMBER_TIME;
}

BottomMenuBarLayer::~BottomMenuBarLayer(){}

void BottomMenuBarLayer::buildUI(float height, Color4B layerColor) {
  layerSize = Size(Director::getInstance()->getWinSize().width, height);
  auto backgroundColor = cocos2d::LayerColor::create(layerColor);
  backgroundColor->setContentSize(layerSize);
  addChild(backgroundColor);
  
  suggestionButton = CustomButton::create(LIGHT_ON_BUTTON_NAME, "", suggestCount, [&, this]{ handleTapOnSuggestionButton(); });
  suggestionButton->setPosition(Vec2(layerSize.width - 48.0, layerSize.height/2.0));
  addChild(suggestionButton);
  
  undoButton = CustomButton::create(UNDO_ICON_NAME, "", undoCount, [&, this]{ handleTapOnUndoButton(); });
  undoButton->setPosition(Vec2(suggestionButton->getPositionX() - 96, suggestionButton->getPositionY()));
  addChild(undoButton);
  
  removeNumberButton = CustomButton::create(REMOVE_NUMBER_ICON_NAME, "", removeNumberCount, [&, this]{ handleTapOnRemoveNumberButton(); });
  removeNumberButton->setPosition(Vec2(undoButton->getPositionX() - 96, suggestionButton->getPositionY()));
  addChild(removeNumberButton);
}

void BottomMenuBarLayer::handleTapOnSuggestionButton() {
  SoundManager::getInstance()->playSound(CLICK_BUTTON_SOUND);
  if(suggestCount <= 0) {
    return;
  };
  suggestCount -= 1;
  suggestionButton->setLabelVisibility(suggestCount > 0);
  suggestionButton->updateText(suggestCount);
  delegate->clickSuggestionButton();
}

void BottomMenuBarLayer::handleTapOnUndoButton() {
  SoundManager::getInstance()->playSound(CLICK_BUTTON_SOUND);
  if(undoCount <= 0) {
    return;
  };
  delegate->clickUndoButton([&, this](bool isCompleted){
    if(isCompleted) {
      this->undoCount -= 1;
      this->undoButton->setLabelVisibility(undoCount > 0);
      this->undoButton->updateText(undoCount);
    }
  });
}

void BottomMenuBarLayer::handleTapOnRemoveNumberButton() {
  SoundManager::getInstance()->playSound(CLICK_BUTTON_SOUND);
  if(removeNumberCount <= 0) {
    return;
  };
  delegate->clickRemoveNumberButton([&, this](bool isCompleted){
    if(isCompleted) {
      this->removeNumberCount -= 1;
      this->removeNumberButton->setLabelVisibility(removeNumberCount > 0);
      this->removeNumberButton->updateText(removeNumberCount);
    }
  });
}

void BottomMenuBarLayer::resetData() {
  undoCount = DEFAULT_UNDO_TIME;
  undoButton->updateText(undoCount);
  undoButton->setLabelVisibility(true);
  
  suggestCount = DEFAULT_SUGGESTION_TIME;
  suggestionButton->updateText(suggestCount);
  suggestionButton->setLabelVisibility(true);
  
  removeNumberCount = DEFAULT_REMOVE_NUMBER_TIME;
  removeNumberButton->updateText(removeNumberCount);
  removeNumberButton->setLabelVisibility(true);
}

void BottomMenuBarLayer::setDelegate(EventClickButtonDelegate* delegate) {
  this->delegate = delegate;
}

Size BottomMenuBarLayer::getContentSize() { return layerSize; }

void BottomMenuBarLayer::setTouchEnabledOnLayer(bool isEnabled) {
  suggestionButton->setTouchEnabled(isEnabled);
  undoButton->setTouchEnabled(isEnabled);
  removeNumberButton->setTouchEnabled(isEnabled);
}
