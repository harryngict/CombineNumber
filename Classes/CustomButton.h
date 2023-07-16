//
//  CustomButton.h
//  CombineNumber
//
//  Created by Harry Nguyen on 16/7/23.
//

#ifndef CustomButton_h
#define CustomButton_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameConfig.h"

using namespace std;
using namespace cocos2d;

class CustomButton : public cocos2d::ui::Button {
public:
  
  static CustomButton* create(const std::string& normalImage, const std::string& selectedImage, int number, function<void()> completion) {
    CustomButton* button = new CustomButton();
    if (button && button->init(normalImage, selectedImage, number, completion)) {
      button->autorelease();
      return button;
    }
    CC_SAFE_DELETE(button);
    return nullptr;
  }
  
  bool init(const std::string& normalImage, const std::string& selectedImage, int number, function<void()> completion) {
    if (!Button::init(normalImage, selectedImage, "", cocos2d::ui::Widget::TextureResType::LOCAL)) {
      return false;
    }
    
    labelNode = cocos2d::Label::createWithTTF(std::to_string(number), FONT_NAME_NUMBER_LABEL, 40);
    labelNode->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    labelNode->setPosition(cocos2d::Vec2(getContentSize().width, getContentSize().height));
    addChild(labelNode);
    
    addAnimationWhenTapOnButton(completion);
    return true;
  }
  
  
  static CustomButton* create(const std::string& normalImage, const std::string& selectedImage, function<void()> completion) {
    CustomButton* button = new CustomButton();
    if (button && button->init(normalImage, selectedImage, completion)) {
      button->autorelease();
      return button;
    }
    CC_SAFE_DELETE(button);
    return nullptr;
  }
  
  bool init(const std::string& normalImage, const std::string& selectedImage, function<void()> completion) {
    if (!Button::init(normalImage, selectedImage, "", cocos2d::ui::Widget::TextureResType::LOCAL)) {
      return false;
    }
    addAnimationWhenTapOnButton(completion);
    return true;
  }
  
  void setLabelVisibility(bool isVisibility) {
    labelNode->setVisible(isVisibility);
  }
  
  void updateText(int number) {
    labelNode->setString(std::to_string(number));
  }
  
private:
  cocos2d::Label* labelNode;
  
  void addAnimationWhenTapOnButton(function<void()> completion) {
    addTouchEventListener([&, this, completion](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
      if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
        auto scaleUp = cocos2d::ScaleTo::create(0.1f, 1.2f);
        runAction(scaleUp);
      } else if (type == cocos2d::ui::Widget::TouchEventType::ENDED || type == cocos2d::ui::Widget::TouchEventType::CANCELED) {
        auto scaleDown = cocos2d::ScaleTo::create(0.1f, 1.0f);
        runAction(scaleDown);
        completion();
      }
    });
  }
};

#endif /* CustomButton_h */
