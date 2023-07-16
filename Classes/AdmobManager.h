//
//  AdmobManager.h
//  Combine Number
//
//  Created by Harry Nguyen on 15/7/23.
//

#ifndef AdmobManager_h
#define AdmobManager_h

#include <stdio.h>
#include <string>

class AdmobManager {
private:
  static AdmobManager* instance;
public:
  static AdmobManager* getInstance();
  void init(const std::string &bannerId, const std::string &interstitialId);
  void showBanner();
  void showInterstitial(std::function<void(bool)> completion);
  bool isBannerViewVisible();
};

#endif /* AdmobManager_h */
