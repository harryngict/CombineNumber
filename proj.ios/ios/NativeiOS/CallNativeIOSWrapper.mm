//
//  CallNativeIOSWrapper.m
//  Combine Number
//
//  Created by Harry Nguyen on 15/7/23.
//

#import "CallNativeIOSWrapper.h"
#import "AdmobIOS.h"
#import "HapticEngine.h"
#import "GameCenterHelper.h"


static CallNativeIOSWrapper _sCallNativeIOSWrapper;

CallNativeIOSWrapper* CallNativeIOSWrapper::getInstance() {
  return &_sCallNativeIOSWrapper;
}

void CallNativeIOSWrapper::init(const std::string &bannerId, const std::string &interstitialId) {
  NSString *banner = [NSString stringWithUTF8String:bannerId.data()];
  NSString* interstitial = [NSString stringWithUTF8String:interstitialId.data()];
  [[AdmobIOS sharedAdmob] setBannerId:banner];
  [[AdmobIOS sharedAdmob] setInterstitialId:interstitial];
}

void CallNativeIOSWrapper::showBanner() {
  [[AdmobIOS sharedAdmob] showBanner];
}

void CallNativeIOSWrapper::showInterstitial(std::function<void(bool)> completion) {
  [[AdmobIOS sharedAdmob] showInterstitial:^(BOOL finished) {
    completion(finished);
  }];
}

bool CallNativeIOSWrapper::isBannerViewVisible() {
  return [[AdmobIOS sharedAdmob] isBannerViewVisible];
}

void CallNativeIOSWrapper::playHaptic() {
  [[HapticEngine sharedInstance] playHaptic];
}


void CallNativeIOSWrapper::showLeaderboard() {
  [[GameCenterHelper sharedInstance] showLeaderboard];
}

void CallNativeIOSWrapper::reportScore(int score) {
  [[GameCenterHelper sharedInstance] reportScore: score];
}
