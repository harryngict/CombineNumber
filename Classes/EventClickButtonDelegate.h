//
//  EventClickButtonDelegate.h
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#ifndef EventClickButtonDelegate_h
#define EventClickButtonDelegate_h

#include <stdio.h>
using namespace std;

class EventClickButtonDelegate {
public:
  virtual void clickBackButton() = 0;
  virtual void clickResetButton() = 0;
  virtual void clickSuggestionButton() = 0;
  virtual void clickUndoButton(function<void(bool)> completion) = 0;
  virtual void clickRemoveNumberButton(function<void(bool)> completion) = 0;
  virtual void showReachToLitmitedUndoMessage(const string& message) = 0;
};

#endif /* EventClickButtonDelegate_h */
