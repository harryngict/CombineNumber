//
//  GameBoardDelegate.h
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#ifndef GameBoardDelegate_h
#define GameBoardDelegate_h

class GameBoardDelegate {
public:
  virtual void fireGameOverEvent() = 0;
  virtual void fireEarnScoreAndMaximumNumber(int score, int maximumNumber) = 0;
  virtual void fireShowGuidePopUp(bool isShow) = 0;
  virtual void activeTouchTopBarMenuLayer() = 0;
  virtual void readyToShowAdvertisement() = 0;
  virtual void updateMessageLabel(const string& message, bool animation) = 0;
};


#endif /* GameBoardDelegate_h */
