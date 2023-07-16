//
//  UndoData.h
//  CombineNumber
//
//  Created by Hoang Nguyen on 22/7/23.
//

#ifndef UndoData_h
#define UndoData_h

#include <stdio.h>
using namespace std;

class UndoData {
protected:
  vector<int> values;
  int earnPoint, maxNumber;
public:
  UndoData(vector<int> values, int earnPoint, int maxNumber) {
    this->values = values;
    this->earnPoint = earnPoint;
    this->maxNumber = maxNumber;
  };
  
  vector<int> getValues() { return values; };
  int getEarnPont() { return earnPoint; };
  int getMaxNumber() { return maxNumber; }
};


#endif /* UndoData_h */
