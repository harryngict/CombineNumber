//
//  ColorFactory.h
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#ifndef ColorFactory_h
#define ColorFactory_h

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class ColorFactory {
protected:
  static ColorFactory* singleton_;
  ColorFactory() {};
public:
  ColorFactory(ColorFactory &other) = delete;
  void operator=(const ColorFactory &) = delete;
  static ColorFactory *GetInstance();
  Color3B getTextColor();
  Color3B getBackgroundColorWhenRemoveMode();
  Color3B getWarningMessageColor();
  Color4F getCircleColor(int number);
  Color4F getLineColor();
  Color4B getBackgroundColor();
  Color4B getTopMenuBarLayerColor();
  Color4B getGameOverLayerColor();
  Color4B getGuideLineLayerColor();
};
#endif /* ColorFactory_h */
