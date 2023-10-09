#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void rotateMatrix(FILE * f, char rotate[][10]) {
  char line[12];  //为什么要十二个字符才包括换行符呢？？？

  int count = 0;
  char * lineEnd;
  while (fgets(line, 12, f) != NULL) {
    if ((lineEnd = strchr(line, '\n')) == NULL) {
      fprintf(stderr, "too long for one line!");
      exit(EXIT_FAILURE);
    }
    if ((lineEnd - line) != 10) {
      fprintf(stderr, "too short for one line!");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 10; i++) {
      rotate[i][9 - count] = line[i];
    }
    count++;
    if (count > 10) {
      fprintf(stderr, "too many lines");
      exit(EXIT_FAILURE);
    }
  }

  if (count < 10) {
    fprintf(stderr, "too few lines");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "invalid input!");
    return (EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "could not open the file!");
    return EXIT_FAILURE;
  }
  char rotate[10][10];
  rotateMatrix(f, rotate);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", rotate[i][j]);
    }
    printf("\n");
  }

  if (fclose(f) != 0) {
    fprintf(stderr, "could not close the file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
