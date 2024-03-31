#ifndef RollingList_h
#define RollingList_h

class RollingList {
public:
  RollingList(int _len, int _paddedLen);
  ~RollingList();
  void test();
  float operator[](int);
  void set(float _num);
  int len();
  float *toPaddedArray();

private:
  float *arr;
  float *paddedArr;
  int curId = 0;
  int paddedLen;
  int leng;

};

#endif
