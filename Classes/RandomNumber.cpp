//
//  RandomNumber.cpp
//  Combine Number
//
//  Created by Harry Nguyen on 14/7/23.
//

#include "RandomNumber.h"
#include "GameConfig.h"

RandomNumber* RandomNumber::singleton_= nullptr;;

RandomNumber *RandomNumber::GetInstance() {
  if(singleton_== nullptr) { singleton_ = new RandomNumber(); }
  return singleton_;
}

int RandomNumber::getRandomNumber(vector<int> buckets) {
  if(buckets.empty()) {
    return RandomHelper::random_int(1, 2);
  } else {
    int minValue, maxValue;
    if(buckets.size() == 1) {
      maxValue = buckets[0];
      minValue = maxValue + 1;
    } else {
      minValue = *std::min_element(buckets.begin(), buckets.end());
      maxValue = *std::max_element(buckets.begin(), buckets.end());
    }
    int start = max(1, minValue);
    int end = max(2, maxValue);
    return RandomHelper::random_int(min(start, end), max(start, end));
  }
  
}

int RandomNumber::getRandomNumber(int maximum) {
  return RandomHelper::random_int(1, max(2, maximum));;
}

/// This function is used when debug and test logic game
int RandomNumber::simulateNumber(int row, int column) {
  int values[TOTAL_ROW_CELL][TOTAL_COLUMN_CELL];
  values[0][0] = 2;
  values[0][1] = 2;
  values[0][2] = 1;
  values[0][3] = 2;
  values[0][4] = 1;
  values[0][5] = 2;
  
  values[1][0] = 2;
  values[1][1] = 1;
  values[1][2] = 1;
  values[1][3] = 2;
  values[1][4] = 1;
  values[1][5] = 1;
  
  values[2][0] = 1;
  values[2][1] = 1;
  values[2][2] = 2;
  values[2][3] = 1;
  values[2][4] = 1;
  values[2][5] = 2;
  
  values[3][0] = 2;
  values[3][1] = 2;
  values[3][2] = 2;
  values[3][3] = 2;
  values[3][4] = 1;
  values[3][5] = 1;
  
  values[4][0] = 2;
  values[4][1] = 1;
  values[4][2] = 2;
  values[4][3] = 2;
  values[4][4] = 2;
  values[4][5] = 1;
  
  values[5][0] = 2;
  values[5][1] = 1;
  values[5][2] = 2;
  values[5][3] = 1;
  values[5][4] = 1;
  values[5][5] = 1;
  
  return values[row][column];
}
