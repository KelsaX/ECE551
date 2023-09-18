#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned real_ans = power(x, y);
  if (real_ans == expected_ans) {
    printf("This test passed for (%d, %d)", x, y);
  }
  else {
    printf("This test failed\n for (%d, %d)", x, y);
    exit(EXIT_FAILURE);
  }
}

int main() {
  run_check(2, 3, 8);
  run_check(0, 0, 1);
  run_check(10, 0, 1);
  run_check(0, 1000, 0);
  run_check(10, 3, 1000);
  run_check(5, 2, 25);
  run_check(1, 100, 1);
  run_check(3, 3, 27);
  run_check(10, 6, 1000000);
  exit(EXIT_SUCCESS);
}
