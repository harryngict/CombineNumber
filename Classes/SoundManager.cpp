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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "CallNativeIOSWrapper.h"
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

SoundManager* SoundManager::singleton_= nullptr;;

SoundManager *SoundManager::getInstance() {
  if(singleton_== nullptr) { singleton_ = new SoundManager(); }
  return singleton_;
}

void SoundManager::playSound(int tag) {
  if(!UserDefault::getInstance()->getBoolForKey(KEY_SOUND_GAME, true)) { return; }
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

void SoundManager::playHaptic() {
  if(!UserDefault::getInstance()->getBoolForKey(KEY_HAPTIC_GAME, true)) { return; }
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
  CallNativeIOSWrapper::getInstance()->playHaptic();
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  cocos2d::JniMethodInfo methodInfo;
  if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "playHapticFeedback", "()V")) {
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
  }
#endif
}
