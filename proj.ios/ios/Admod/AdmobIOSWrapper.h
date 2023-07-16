//
//  AdmobIOSWrapper.h
//  Combine Number
//
//  Created by Harry Nguyen on 15/7/23.
//

#ifndef AdmobIOSWrapper_h
#define AdmobIOSWrapper_h

#include "cocos2d.h"

class AdmobIOSWrapper {
public:
  static AdmobIOSWrapper* getInstance();
  void init(const std::string &bannerId, const std::string &interstitialId);
  void showBanner();
  void showInterstitial(std::function<void(bool)> completion);
};

#endif /* AdmobIOSWrapper_h */
