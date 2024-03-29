#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t expect) {
  size_t ans = maxSeq(array, n);
  if (ans == expect) {
    printf("test passed");
  }
  else {
    printf("test failed");
    exit(EXIT_FAILURE);
  }
}

int main() {
  int array1[] = {1, 2, 1, 3, 5, 3, 2, 6};
  // int* array2={9,3,5,3,2,6};
  run_check(array1, sizeof(array1), 3);

  //  int array2[] = {1, 2, 3, 1, 3};
  // run_check(array2, sizeof(array2), 3);

  // int array3[] = {9,8,7,6,5,4,3,2,1};
  int array3[] = {-1, -2, -1, 0, 2};
  run_check(array3, sizeof(array3), 4);

  int array4[] = {1, -3, -3, -7, -9};
  run_check(array4, 5, 1);

  int array5[] = {1, -123, -1234, -12345, -123456, -1234567};
  run_check(array5, 0, 0);
  return EXIT_SUCCESS;
}
