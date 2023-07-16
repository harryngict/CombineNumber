//
//  SoundManager.h
//  CombineNumber
//
//  Created by Harry Nguyen on 18/7/23.
//

#ifndef SoundManager_h
#define SoundManager_h

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class SoundManager {
protected:
  static SoundManager* singleton_;
  SoundManager() {};
public:
  static SoundManager* getInstance();
  void playSound(int tag);
};

#endif /* SoundManager_h */
