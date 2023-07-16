//
//  AdmobManager.cpp
//  Combine Number
//
//  Created by Harry Nguyen on 15/7/23.
//

#include "AdmobManager.h"
#include "cocos2d.h"
using namespace std;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "CallNativeIOSWrapper.h"
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

AdmobManager* AdmobManager::instance= nullptr;

AdmobManager* AdmobManager::getInstance() {
  if(instance == nullptr) { instance = new AdmobManager(); }
  return instance;
}

void AdmobManager::init(const std::string &bannerId, const std::string &interstitialId) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
  CallNativeIOSWrapper::getInstance()->init(bannerId, interstitialId);
#endif
}

void AdmobManager::showBanner() {
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

void AdmobManager::showInterstitial(function<void(bool)> completion) {
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

bool AdmobManager::isBannerViewVisible() {
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
