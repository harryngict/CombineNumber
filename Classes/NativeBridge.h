//
//  NativeBridge.h
//  CombineNumber
//
//  Created by Hoang Nguyen on 28/7/23.
//

#ifndef NativeBridge_h
#define NativeBridge_h

#include <stdio.h>
#include <string>
using namespace std;

class NativeBridge {
private:
  static NativeBridge* instance;
public:
  static NativeBridge* getInstance();
  void init(const std::string &bannerId, const std::string &interstitialId);
  void showBanner();
  void showInterstitial(std::function<void(bool)> completion);
  bool isBannerViewVisible();
  void playSound(int tag);
  void playBackgroundSound(bool isTurnOn);
  void playHaptic();  
  void showLeaderboard();
  void reportScore(int score);
  bool isLeaderBoardAvailable();
};

#endif /* NativeBridge_h */
