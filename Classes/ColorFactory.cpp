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
  int red = (number * 73) % 256; // Manipulate the red component based on the number
  int green = (number * 127) % 256; // Manipulate the green component based on the number
  int blue = (number * 179) % 256; // Manipulate the blue component based on the number
  return Color4F(red, green, blue, 0.96);
}
Color4B ColorFactory::getEmptyCellColor(int row, int column) {
  int index = row + column * TOTAL_ROW_CELL;
  Color4B cellColor = index % 2 == 0 ? Color4B::BLACK : Color4B::GREEN;
  return cellColor;
}

Color3B ColorFactory::getTextColor() { return Color3B::WHITE; }

Color4F ColorFactory::getLineColor() { return Color4F::RED; }

Color4B ColorFactory::getTopMenuBarLayerColor() { return Color4B::MAGENTA; }

Color4B ColorFactory::getGameOverLayerColor() { return Color4B::RED; }

Color4B ColorFactory::getGuideLineLayerColor() { return Color4B::ORANGE; }

Color4B ColorFactory::getBackgroundColor() { return Color4B(135, 206, 235, 220); }
