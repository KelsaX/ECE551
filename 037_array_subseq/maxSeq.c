#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n) {
  size_t countMax = 1;
  size_t count = 1;
  if (n == 0) {
    countMax = 0;
  }
  for (size_t i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      count++;
    }
    else {
      count = 1;
    }
    if (count > countMax) {
      countMax = count;
    }
  }
  return countMax;
}
