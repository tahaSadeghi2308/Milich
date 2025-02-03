#include "../include/memoryManager.h"
#include <iostream>

using namespace std;

// TEST : PENDING ....
template<typename T>
T* makeTwice(T** currentMem , int currentLen){
  T* temp = new T[currentLen * 2];  
  // copy
  for(int i {0}; i < currentLen; i++){
    temp[i] = *((*currentMem + i));
  }
  delete[] *currentMem;
  return temp;
}
