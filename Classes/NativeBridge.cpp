//
//  NativeBridge.cpp
//  CombineNumber
//
//  Created by Hoang Nguyen on 28/7/23.
//

#include "NativeBridge.h"
#include "cocos2d.h"
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
using namespace cocos2d;

NativeBridge* NativeBridge::instance= nullptr;

NativeBridge* NativeBridge::getInstance() {
  if(instance == nullptr) { instance = new NativeBridge(); }
  return instance;
}

void NativeBridge::init(const std::string &bannerId, const std::string &interstitialId) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
  CallNativeIOSWrapper::getInstance()->init(bannerId, interstitialId);
#endif
}

void NativeBridge::showBanner() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
  CallNativeIOSWrapper::getInstance()->showBanner();
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  cocos2d::JniMethodInfo minfo;
  if (cocos2d::JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","showBanner","()V")) {
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
  }
#endif
}

void NativeBridge::showInterstitial(function<void(bool)> completion) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
  CallNativeIOSWrapper::getInstance()->showInterstitial(completion);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  cocos2d::JniMethodInfo minfo;
  if (cocos2d::JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","showInterstitial","()V")) {
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
  }
#endif
}

bool NativeBridge::isBannerViewVisible() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
  return CallNativeIOSWrapper::getInstance()->isBannerViewVisible();
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  JNIEnv* env = cocos2d::JniHelper::getEnv();
  // Get the Java class and method IDs
  jclass javaClass = env->FindClass("org/cocos2dx/cpp/AppActivity");
  jmethodID javaMethod = env->GetStaticMethodID(javaClass, "isBannerViewVisible", "()Z");
  
  // Call the Java function and get the result
  jboolean jResult = env->CallStaticBooleanMethod(javaClass, javaMethod);
  
  // Convert the Java boolean result to C++ bool
  bool result = (jResult == JNI_TRUE);
  
  // Release local references
  env->DeleteLocalRef(javaClass);
  
  return result;
#endif
}

void NativeBridge::playSound(int tag) {
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

void NativeBridge::playHaptic() {
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

void NativeBridge::showLeaderboard() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
  CallNativeIOSWrapper::getInstance()->showLeaderboard();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  cocos2d::JniMethodInfo methodInfo;
  if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "showLeaderboard", "()V")) {
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
  }
#endif
}

void NativeBridge::reportScore(int score) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
  CallNativeIOSWrapper::getInstance()->reportScore(score);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  cocos2d::JniMethodInfo methodInfo;
  if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "reportScore", "(I)V")) {
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, score);
  }
#endif
}

bool NativeBridge::isLeaderBoardAvailable() {
  bool result = true;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
   JNIEnv* env = cocos2d::JniHelper::getEnv();
   jclass javaClass = env->FindClass("org/cocos2dx/cpp/AppActivity");
   jmethodID methodID = env->GetStaticMethodID(javaClass, "isGooglePlayServicesAvailable", "()Z");
   if (javaClass && methodID) {
       result = (bool)env->CallStaticBooleanMethod(javaClass, methodID);
       env->DeleteLocalRef(javaClass);
   }
#endif
   return result;
}
