#include <stdio.h>
#include <stdlib.h>
//I've provided "min" and "max" functions in
//case they are useful to you
int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}
int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}
/*注意：当宽和高为负值时，并不是代表是错的设定，而是意味着向x或者y轴的负方
向延伸*/
//Declare your rectangle structure here!
struct _rectangle {
  int x;
  int y;
  int width;
  int height;
};

typedef struct _rectangle rectangle;

rectangle canonicalize(rectangle r) {
  //WRITE THIS FUNCTION

  if (r.width < 0) {
    r.x = r.x + r.width;
    r.width = 0 - r.width;
  }
  if (r.height < 0) {
    r.y = r.y + r.height;
    r.height = 0 - r.height;
  }
  return r;
}
rectangle intersection(rectangle r1, rectangle r2) {
  //WRITE THIS FUNCTION
  r1 = canonicalize(r1);
  r2 = canonicalize(r2);
  rectangle r;
  if ((r1.x <= (r2.x + r2.width)) && ((r1.y + r1.height) >= r2.y) &&
      (r2.x <= (r1.x + r1.width)) && ((r2.y + r2.height) >= r1.y)) {
    int rightSide = min((r1.x + r1.width), (r2.x + r2.width));
    r1.x = max(r1.x, r2.x);

    r1.width = rightSide - r1.x;

    int upSide = min((r1.y + r1.height), (r2.y + r2.height));
    r1.y = max(r1.y, r2.y);
    r1.height = upSide - r1.y;
  }
  else if ((r2.x <= (r1.x + r1.width)) && ((r2.y + r2.height) >= r1.y) &&
           (r1.x <= (r2.x + r2.width)) && ((r1.y + r1.height) >= r2.y)) {
    r = r1;
    r1 = r2;
    r2 = r;

    int rightSide = min((r1.x + r1.width), (r2.x + r2.width));
    r1.x = max(r1.x, r2.x);
    r1.width = rightSide - r1.x;

    int upSide = min((r1.y + r1.height), (r2.y + r2.height));
    r1.y = max(r1.y, r2.y);
    r1.height = upSide - r1.y;
  }
  else {
    r1.width = 0;
    r1.height = 0;
  }

  return r1;
}

//You should not need to modify any code below this line
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, r.x + r.width, r.y + r.height);
  }
}

int main(void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);

  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  //test everything with r1
  //在这个地方调用intersection函数之前的printangle函数并没有真的改变r
  rectangle i = intersection(r1, r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1, r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);

  i = intersection(r1, r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1, r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2, r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2, r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);

  i = intersection(r2, r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2, r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3, r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3, r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);

  i = intersection(r3, r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3, r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4, r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4, r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);

  i = intersection(r4, r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4, r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);

  return EXIT_SUCCESS;
}
