#include "rollingList.h"
RollingList::RollingList(int _len, int _paddedLen) {
  leng = _len;
  paddedLen = _paddedLen;
  arr = (float*)malloc(leng * sizeof(float));
  paddedArr = (float*)malloc(paddedLen * sizeof(float));

  for (int ii = 0; ii < leng; ii++) {
    arr[ii] = 0;
    
  }
  for (int ii = 0; ii < paddedLen; ii++) {
    paddedArr[ii] = 0;
  }
  
}

RollingList::~RollingList() {
  free(arr);
}

int RollingList::len() {
  return leng;
}

float* RollingList::toPaddedArray() {
  for (int ii = 0;ii < leng;ii++){
    int id = (curId + ii) % leng;
    paddedArr[ii] = arr[id];
  }
  for (int ii = leng; ii < paddedLen; ii++) {
    paddedArr[ii] = 0;
  }
  return paddedArr;
}

float RollingList::operator[](int index) {
  if (index < 0){
    Serial.println("No negative indexes");
    return -1;
  }
  int id = (curId + index) % leng;
  return arr[id];  
}

void RollingList::set(float num) {
  arr[curId] = num;
  curId = (curId + 1) % leng;
}
