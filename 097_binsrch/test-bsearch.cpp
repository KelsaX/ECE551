#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"
class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocayions in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
int binarySearchForZero(Function<int, int> * f, int low, int high);
void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  unsigned maxinvoke = 0;
  if (high > low) {
    maxinvoke = log2(high - low) + 1;
  }
  else {
    maxinvoke = 1;
  }
  CountedIntFn checkcount(maxinvoke, f, mesg);
  int ans = binarySearchForZero(&checkcount, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "The answer is wrong in %s\n", mesg);
    exit(EXIT_FAILURE);
  }
}
class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class PowerFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg * arg; }
};

class DoubleFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 2 * arg; }
};
int main(int argc, char ** argv) {
  SinFunction sin1;
  check(&sin1, 0, 150000, 52359, "sin1");

  PowerFunction power1;
  check(&power1, -2, 6, 0, "power1_1");
  check(&power1, 2, 8, 2, "power1_2");
  check(&power1, -2, 6, 0, "power1_3");
  check(&power1, -8, -2, -8, "power1_4");

  DoubleFunction double1;
  check(&double1, -8, -2, -3, "double1_1");
  check(&double1, -1, 3, 0, "double1_2");
  std::cout << "sucessfull";
  return (EXIT_SUCCESS);
}
