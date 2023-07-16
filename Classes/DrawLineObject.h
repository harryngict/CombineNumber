//
//  DrawLineObject.h
//  Combine Number
//
//  Created by Harry Nguyen on 13/7/23.
//

#ifndef DrawLineObject_h
#define DrawLineObject_h

#include "cocos2d.h"
using namespace cocos2d;

class DrawLineObject {
private:
  Vec2 startMatrix, endMatrix;
  DrawNode* drawNode;
  
public:
  
  DrawLineObject(DrawNode* drawNode, const Vec2& startMatrix, const Vec2& endMatrix);
  
  bool operator==(DrawLineObject const& obj) { return startMatrix == obj.startMatrix && endMatrix == obj.endMatrix; }

  virtual ~DrawLineObject();
  
  Vec2 getStartMatrix() { return startMatrix; };
  
  Vec2 getEndMatrix() { return endMatrix; };
  
  DrawNode* getDrawNode() { return drawNode; };
};

#endif /* DrawLineObject_h */
