//
//  ColorFactory.cpp
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#include "ColorFactory.h"
#include "GameConfig.h"

ColorFactory* ColorFactory::singleton_= nullptr;;

ColorFactory *ColorFactory::GetInstance() {
  if(singleton_== nullptr) { singleton_ = new ColorFactory(); }
  return singleton_;
}

Color4F ColorFactory::getCircleColor(int number) {
  int red = (number * 73) % 256;
  int green = (number * 127) % 256;
  int blue = (number * 179) % 256;
  return Color4F(red, green, blue, 0.96);
}

Color3B ColorFactory::getWarningMessageColor() { return Color3B::WHITE; }

Color3B ColorFactory::getTextColor() { return Color3B::WHITE; }

Color4F ColorFactory::getLineColor() { return Color4F::RED; }

Color4B ColorFactory::getTopMenuBarLayerColor() { return Color4B(0, 48, 117, 255);  }

Color4B ColorFactory::getGameOverLayerColor() { return Color4B(241, 26, 123, 255); }

Color4B ColorFactory::getGuideLineLayerColor() { return Color4B(252, 115, 0, 255); }

Color4B ColorFactory::getBackgroundColor() { return Color4B(205, 197, 174, 255); }

Color3B ColorFactory::getBackgroundColorWhenRemoveMode() { return Color3B(10, 38, 71); };
