#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
void record_letter(FILE * f, char * arr) {
  int c;

  char firstA = 'a';
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      arr[c - firstA]++;
    }
  }
}
int find_most(char * arr, int n) {
  int largestInd = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] > arr[largestInd]) {
      largestInd = i;
    }
  }
  return largestInd;
}
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  char arr[26] = {0};

  record_letter(f, arr);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  int size_arr = 26;
  int key = 0;
  key = find_most(arr, size_arr) - 4;
  printf("%d\n", key);
  return EXIT_SUCCESS;
}
