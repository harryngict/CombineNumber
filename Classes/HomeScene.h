//
//  HomeScene.h
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#ifndef HomeScene_h
#define HomeScene_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocos2d::ui;

class HomeScene : public cocos2d::Layer {
private:
  Size winSize;
public:
  static Scene* createScene();
  HomeScene();
  virtual ~HomeScene();
  virtual bool init();
};
#endif /* HomeScene_h */
