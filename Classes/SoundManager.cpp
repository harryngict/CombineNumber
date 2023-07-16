//
//  SoundManager.cpp
//  CombineNumber
//
//  Created by Harry Nguyen on 18/7/23.
//

#include "SoundManager.h"
#include "GameConfig.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

SoundManager* SoundManager::singleton_= nullptr;;

SoundManager *SoundManager::getInstance() {
  if(singleton_== nullptr) { singleton_ = new SoundManager(); }
  return singleton_;
}

void SoundManager::playSound(int tag) {
  bool isSoundOn = UserDefault::getInstance()->getBoolForKey(KEY_SOUND_GAME, false);
  if(!isSoundOn) { return; }
  std::string filePath = "";
  switch (tag) {
    case CLICK_BUTTON_SOUND:
      filePath = "click_button_sound.mp3";
      break;
    case TOUCH_NUMBER_SOUND:
      filePath = "touch_number_sound.mp3";
      break;
    case REMOVE_NUMBER_SOUND:
      filePath = "remove_number_sound.mp3";
      break;
    case INCREASE_NEW_NUMBER_SOUND:
      filePath = "increase_number_sound.mp3";
      break;
    case GAME_OVER_SOUND:
      filePath = "game_over_sound.mp3";
      break;
    default: break;
  }
  if(filePath.empty()) { return; }
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
  audio->preloadEffect(filePath.c_str());
  audio->playEffect(filePath.c_str());
}
