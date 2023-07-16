//
//  GameOverLayer.h
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#ifndef GameOverLayer_h
#define GameOverLayer_h

#include <stdio.h>
#include "cocos2d.h"
#include "EventClickButtonDelegate.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

class GameOverLayer: public Layer {
private:
  Size layerSize;
  EventClickButtonDelegate* delegate = nullptr;
  void handleTapOnBackButton();
  void handleTapOnResetButton();
public:
  virtual ~GameOverLayer();
  void buildUI(float height, Color4B layerColor);
  void setDelegate(EventClickButtonDelegate* delegate);
  void moveUpAndDisAppearAnimation(function<void()> completion);
  void moveDownAndAppearAnimation();
};

#endif /* GameOverLayer_h */
