#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
char ** readString(FILE * f, size_t * sizeArr) {
  char * line = NULL;
  size_t lineSize = 0;
  int char_count = 0;
  char ** strArr = NULL;
  size_t totalLine = 0;

  while ((char_count = getline(&line, &lineSize, f)) != -1) {
    strArr = realloc(strArr, (totalLine + 1) * sizeof(*strArr));
    strArr[totalLine] = malloc((char_count + 1) * sizeof(char));
    strcpy(strArr[totalLine], line);

    totalLine++;
  }
  free(line);
  *sizeArr = totalLine;
  sortData(strArr, totalLine);
  return strArr;
}
void printRead(char ** strArr, size_t sizeArr) {
  for (size_t i = 0; i < sizeArr; i++) {
    printf("%s", strArr[i]);
  }
}
void freeStrArr(char ** strArr, size_t sizeArr) {
  for (size_t i = 0; i < sizeArr; i++) {
    free(strArr[i]);
  }
  free(strArr);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    size_t sizeArr = 0;
    char ** strArr = readString(stdin, &sizeArr);
    printRead(strArr, sizeArr);
    freeStrArr(strArr, sizeArr);
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE * f;
      if ((f = fopen(argv[i], "r")) == NULL) {
        fprintf(stderr, "could not open the file: %s!", argv[i]);
        exit(EXIT_FAILURE);
      }

      size_t sizeArr = 0;
      char ** strArr = readString(f, &sizeArr);

      printRead(strArr, sizeArr);
      freeStrArr(strArr, sizeArr);
      if (fclose(f) != 0) {
        fprintf(stderr, "could not close the file:%s!", argv[i]);
        exit(EXIT_FAILURE);
      }
    }
  }
  return EXIT_SUCCESS;
}
