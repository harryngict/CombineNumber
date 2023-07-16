//
//  RandomNumber.h
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#ifndef RandomNumber_h
#define RandomNumber_h

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class RandomNumber {
protected:
  static RandomNumber* singleton_;
  RandomNumber() { srand(static_cast<unsigned int>(time(nullptr))); };
public:
  RandomNumber(RandomNumber &other) = delete;
  void operator=(const RandomNumber &) = delete;
  static RandomNumber *GetInstance();
  int getRandomNumber(int maximum);
  int getRandomNumber(vector<int> buckets);
  
  /// This function is used when debug and test logic game
  int simulateNumber(int row, int column);
};

#endif /* RandomNumber_h */
