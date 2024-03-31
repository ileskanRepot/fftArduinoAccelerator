#ifndef RollingList_h
#define RollingList_h

/**
 * @brief Simple implementation of rolling list
 * 
 */
class RollingList {
public:
  /**
   * Constuctor to Rolling list
   * 
   * Array where we can keep _len last numbers of dataset stored. 
   * Replacing the oldes element in array can be done in O(1) time.
   * It malloc @_len + @_paddedLen amount of float data.
   * 
   * @param _len length of the array in which we will update values
   * @param _paddedLen length of the array which have the values in correct order 
   */
  RollingList(int _len, int _paddedLen);

  /**
   * Destuctor of the class
   * 
   * Free's the rolling array and the array in which we have the values in correct order
   */
  ~RollingList();

  /**
   * Gets element from the array
   * 
   * 0 -> Oldest element in the array
   * _len - 1 -> Newest element in the array
   * 
   * @return Number in that index
   */
  float operator[](int);

  /**
   * Setter for values in array
   * 
   * Replaces the oldest element in array with @_num
   * 
   * @param _num the number which we will set
   */
  void set(float _num);

  /**
   * Getter for the length of the rolling array
   * 
   * Replaces the oldest element in array with @_num
   * 
   * @return Length of the array
   */
  int len();
  
  /**
   * Computes the rolling list to regular block of memory
   * 
   * @return pointer to the array. This never changes
   */
  float *toPaddedArray();

private:
  float *arr;
  float *paddedArr;
  int curId = 0;
  int paddedLen;
  int leng;

};

#endif
