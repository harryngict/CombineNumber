//
//  DrawLineObject.cpp
//  Combine Number
//
//  Created by Harry Nguyen on 13/7/23.
//

#include "DrawLineObject.h"

DrawLineObject::DrawLineObject(DrawNode* drawNode, const Vec2& startMatrix, const Vec2& endMatrix) {
  this->drawNode = drawNode;
  this->startMatrix = startMatrix;
  this->endMatrix = endMatrix;
}

DrawLineObject::~DrawLineObject() { drawNode = nullptr; }
