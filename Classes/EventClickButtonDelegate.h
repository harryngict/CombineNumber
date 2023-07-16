//
//  EventClickButtonDelegate.h
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#ifndef EventClickButtonDelegate_h
#define EventClickButtonDelegate_h

class EventClickButtonDelegate {
public:
  virtual void clickBackButton() = 0;
  virtual void clickResetButton() = 0;
  virtual void clickSuggestionButton() = 0;
};

#endif /* EventClickButtonDelegate_h */
