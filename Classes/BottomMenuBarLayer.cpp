//
//  BottomMenuBarLayer.cpp
//  CombineNumber
//
//  Created by Hoang Nguyen on 21/7/23.
//

#include "BottomMenuBarLayer.h"
#include "NativeBridge.h"

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
  
  bool isSoundOn = UserDefault::getInstance()->getBoolForKey(KEY_SOUND_GAME, true);
  soundButton = CustomButton::create(isSoundOn ? SOUND_BUTTON_ON_NAME : SOUND_BUTTON_OFF_NAME,
                                     "", [&, this] { handleTapOnSoundButton(); });
  soundButton->setPosition(Vec2(48.0, suggestionButton->getPositionY()));
  addChild(soundButton);
  
  bool isHapticOn = UserDefault::getInstance()->getBoolForKey(KEY_HAPTIC_GAME, true);
  hapticButton = CustomButton::create(isHapticOn ? HAPTIC_BUTTON_ON_NAME : HAPTIC_BUTTON_OFF_NAME,
                                      "", [&, this] { handleTapOnHapticButton(); });
  hapticButton->setPosition(Vec2(soundButton->getPositionX() + 96, suggestionButton->getPositionY()));
  addChild(hapticButton);
  
  if(NativeBridge::getInstance()->isLeaderBoardAvailable()) {
    achievementButton = CustomButton::create(TROPHY_ICON_NAME,
                                             "", [&, this] { handleTapOnAchievementButton(); });
    achievementButton->setPosition(Vec2(hapticButton->getPositionX() + 96, suggestionButton->getPositionY()));
    addChild(achievementButton);
  }
}

void BottomMenuBarLayer::handleTapOnSuggestionButton() {
  NativeBridge::getInstance()->playSound(CLICK_BUTTON_SOUND);
  NativeBridge::getInstance()->playHaptic();
  if(suggestCount <= 0) {
    return;
  };
  suggestCount -= 1;
  suggestionButton->setLabelVisibility(suggestCount > 0);
  suggestionButton->updateText(suggestCount);
  delegate->clickSuggestionButton();
}

void BottomMenuBarLayer::handleTapOnUndoButton() {
  NativeBridge::getInstance()->playSound(CLICK_BUTTON_SOUND);
  NativeBridge::getInstance()->playHaptic();
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
  NativeBridge::getInstance()->playSound(CLICK_BUTTON_SOUND);
  NativeBridge::getInstance()->playHaptic();
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
  soundButton->setTouchEnabled(isEnabled);
  hapticButton->setTouchEnabled(isEnabled);
  achievementButton->setTouchEnabled(isEnabled);
}

void BottomMenuBarLayer::handleTapOnSoundButton() {
  if(UserDefault::getInstance()->getBoolForKey(KEY_SOUND_GAME, true)) {
    UserDefault::getInstance()->setBoolForKey(KEY_SOUND_GAME, false);
    soundButton->loadTextureNormal(SOUND_BUTTON_OFF_NAME, cocos2d::ui::Button::TextureResType::LOCAL);
  } else {
    UserDefault::getInstance()->setBoolForKey(KEY_SOUND_GAME, true);
    soundButton->loadTextureNormal(SOUND_BUTTON_ON_NAME, cocos2d::ui::Button::TextureResType::LOCAL);
  }
  NativeBridge::getInstance()->playSound(CLICK_BUTTON_SOUND);
  NativeBridge::getInstance()->playHaptic();
}

void BottomMenuBarLayer::handleTapOnHapticButton() {
  if(UserDefault::getInstance()->getBoolForKey(KEY_HAPTIC_GAME, true)) {
    UserDefault::getInstance()->setBoolForKey(KEY_HAPTIC_GAME, false);
    hapticButton->loadTextureNormal(HAPTIC_BUTTON_OFF_NAME, cocos2d::ui::Button::TextureResType::LOCAL);
  } else {
    UserDefault::getInstance()->setBoolForKey(KEY_HAPTIC_GAME, true);
    hapticButton->loadTextureNormal(HAPTIC_BUTTON_ON_NAME, cocos2d::ui::Button::TextureResType::LOCAL);
  }
  NativeBridge::getInstance()->playSound(CLICK_BUTTON_SOUND);
  NativeBridge::getInstance()->playHaptic();
}

void BottomMenuBarLayer::handleTapOnAchievementButton() {
  NativeBridge::getInstance()->playSound(CLICK_BUTTON_SOUND);
  NativeBridge::getInstance()->playHaptic();
  NativeBridge::getInstance()->showLeaderboard();
}
