//
//  GuideLinePopUpLayer.h
//  Combine Number
//
//  Created by Harry Nguyen on 15/7/23.
//

#ifndef GuideLinePopUpLayer_h
#define GuideLinePopUpLayer_h

#include <stdio.h>
#include "cocos2d.h"
#include "EventClickButtonDelegate.h"
#include "ui/CocosGUI.h"

using namespace std;
using namespace cocos2d;

class GuideLinePopUpLayer: public Layer {
private:
  Size layerSize;
public:
  virtual ~GuideLinePopUpLayer();
  void buildUI(float height, Color4B layerColor);
  void moveUpAndDisAppearAnimation(function<void()> completion);
  void moveDownAndAppearAnimation();
};
#endif /* GuideLinePopUpLayer_h */
