//
//  AdmobIOSWrapper.m
//  Combine Number
//
//  Created by Harry Nguyen on 15/7/23.
//

#import "AdmobIOSWrapper.h"
#import "AdmobIOS.h"

static AdmobIOSWrapper _sAdmobIOSWrapper;

AdmobIOSWrapper* AdmobIOSWrapper::getInstance() {
  return &_sAdmobIOSWrapper;
}

void AdmobIOSWrapper::init(const std::string &bannerId, const std::string &interstitialId) {
  NSString *banner = [NSString stringWithUTF8String:bannerId.data()];
  NSString* interstitial = [NSString stringWithUTF8String:interstitialId.data()];
  [[AdmobIOS sharedAdmob] setBannerId:banner];
  [[AdmobIOS sharedAdmob] setInterstitialId:interstitial];
}

void AdmobIOSWrapper::showBanner() {
  [[AdmobIOS sharedAdmob] showBanner];
}

void AdmobIOSWrapper::showInterstitial(std::function<void(bool)> completion) {
  [[AdmobIOS sharedAdmob] showInterstitial:^(BOOL finished) {
    completion(finished);
  }];
}
