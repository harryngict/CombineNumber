//
//  CallNativeIOSWrapper.h
//  Combine Number
//
//  Created by Harry Nguyen on 15/7/23.
//

#ifndef CallNativeIOSWrapper_h
#define CallNativeIOSWrapper_h

#include "cocos2d.h"

class CallNativeIOSWrapper {
public:
  static CallNativeIOSWrapper* getInstance();
  void init(const std::string &bannerId, const std::string &interstitialId);
  void showBanner();
  void showInterstitial(std::function<void(bool)> completion);
  bool isBannerViewVisible();
  void playHaptic();
};

#endif /* CallNativeIOSWrapper_h */
