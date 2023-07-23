//
//  BottomMenuBarLayer.h
//  CombineNumber
//
//  Created by Hoang Nguyen on 21/7/23.
//

#ifndef BottomMenuBarLayer_h
#define BottomMenuBarLayer_h

#include <stdio.h>
#include "cocos2d.h"
#include "EventClickButtonDelegate.h"
#include "ui/CocosGUI.h"
#include "CustomButton.h"
#include "EventClickButtonDelegate.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

class BottomMenuBarLayer: public Layer {
private:
  int undoCount, suggestCount, removeNumberCount;
  Size layerSize;
  CustomButton* suggestionButton, *undoButton, *removeNumberButton, *soundButton, *hapticButton;
  EventClickButtonDelegate* delegate  = nullptr;
  void handleTapOnUndoButton();
  void handleTapOnSuggestionButton();
  void handleTapOnRemoveNumberButton();
  void handleTapOnSoundButton();
  void handleTapOnHapticButton();
public:
  BottomMenuBarLayer();
  virtual ~BottomMenuBarLayer();
  void buildUI(float height, Color4B layerColor);
  void setDelegate(EventClickButtonDelegate* delegate);
  void resetData();
  Size getContentSize();
  void setTouchEnabledOnLayer(bool isEnabled);
};
#endif /* BottomMenuBarLayer_h */
