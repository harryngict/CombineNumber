//
//  TopMenuBarLayer.h
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#ifndef TopMenuBarLayer_h
#define TopMenuBarLayer_h

#include <stdio.h>
#include "cocos2d.h"
#include "EventClickButtonDelegate.h"
#include "ui/CocosGUI.h"
#include "CustomButton.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

class TopMenuBarLayer: public Layer {
private:
  int currentPoint, currentMaximumNumber;
  Size layerSize;
  EventClickButtonDelegate* delegate  = nullptr;
  Label* scoreLabel;
  Label* maximumNumberLabel;
  CustomButton* backButton, *resetButton, *soundButton;
  Sequence* createLabelAnimation();
  void handleTapOnBackButton();
  void handleTapOnResetButton();
  void handleTapOnSuggestionButton();
  void handleTapOnSoundButton();
public:
  TopMenuBarLayer();
  virtual ~TopMenuBarLayer();
  void buildUI(float height,
               int earnPoint,
               int maximumNumber,
               Color4B layerColor);
  void setDelegate(EventClickButtonDelegate* delegate);
  void updateEarnPoint(int point);
  void updateMaximumNumber(int number);
  void setTouchEnabledOnLayer(bool isEnabled);
  void resetData();
};

#endif /* TopMenuBarLayer_h */
