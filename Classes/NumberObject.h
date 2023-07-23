//
//  NumberObject.h
//  Combine Number
//
//  Created by Harry Nguyen on 12/7/23.
//

#ifndef NumberObject_h
#define NumberObject_h

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class NumberObject: public Node {
private:
  int value, animationStatus;
  bool isMovingUp, isTraveled;
  Vec2 matrix, originPosition;
  Label *numberLabel;
  DrawNode* circleNode, *shadowNode;
  Color4F circleColor;
  EaseSineInOut* createMoveToAnimation(const Vec2& source, const Vec2& destination);
  void drawCircleColorWithShadow(Color4F color);
  void update(float dt);
public:
  NumberObject(int value,
               const Vec2& matrix,
               Color3B textColor,
               Color4F circleColor);
  virtual ~NumberObject();
  const Vec2& getMatrix() { return matrix; };
  int getValue() { return value; };
  Color4F getCircleColor() { return circleColor; };
  void setActiveNumber(bool isActive);
  bool getTraveled() { return isTraveled;};
  bool operator==(NumberObject const& obj){
    return value == obj.value
    && matrix.x == obj.matrix.x
    && matrix.y == obj.matrix.y;
  }
  bool operator!=(NumberObject const& obj){
    return value != obj.value
    || matrix.x != obj.matrix.x
    || matrix.y != obj.matrix.y;
  }
  void setTraveled(bool isTraveled);
  void setAnimationStatus(int status);
  void setMatrix(const Vec2& matrix);
  void setPosition(const Vec2& pos);
  
  void runIncreaseNumberAnimation(int newValue, Color3B newTextColor, Color4F newCircleColor, function<void()> completion);
  void runMoveToAndDisAppearAnimation(const Vec2& source, const Vec2& destination,  function<void()> completion);
  void runMoveToAndAppearAnimation(const Vec2& source, const Vec2& destination, function<void()> completion);
  void runTouchAndDisappearAnimation(function<void()> completion);
};

#endif /* NumberObject_h */
