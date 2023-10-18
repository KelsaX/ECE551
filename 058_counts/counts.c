#include "counts.h"

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * valueCounts = malloc(sizeof(*valueCounts));
  if (valueCounts == NULL) {
    perror("fail to allocate memory for valueCounts");
    exit(EXIT_FAILURE);
  }

  valueCounts->size_valueArr = 0;
  //  one_count_t ** oneValue = NULL;
  valueCounts->valueArr = NULL;
  return valueCounts;
}
int lookUpValue(const char * name, counts_t * valueCounts) {
  // if (valueCounts->size_valueArr == 0) {
  // return 1;
  // }
  for (int i = 0; i < valueCounts->size_valueArr; i++) {
    //  if (valueCounts->valueArr[i] != NULL) {
    if ((strcmp(name, valueCounts->valueArr[i]->value) == 0)) {
      valueCounts->valueArr[i]->valueNum++;
      return 0;
    }
    // }
  }
  return 1;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  /*
  char * newName = "unkown";
  one_count_t * unkown = malloc(sizeof(*unkown));
  if (unkown == NULL) {
    perror("fail to allocate memory for unkown");
    exit(EXIT_FAILURE);
  }
  unkown->valueNum = 0;
  */
  /*
  one_count_t * oneCount = malloc(sizeof(*oneCount));
  if (oneCount == NULL) {
    perror("fail to allocate memory for oneCount struct");
    exit(EXIT_FAILURE);
  }
  oneCount->valueNum = 0;
  */
  /*
  if (name == NULL) {
    unkown->value = malloc((strlen(newName) + 1) * sizeof(char));
    unkown->value = newName;
    unkown->valueNum++;
  }
  */

  if (name == NULL) {
    name = "unknown";
  }
  if (lookUpValue(name, c)) {
    c->size_valueArr++;
    c->valueArr = realloc(c->valueArr, c->size_valueArr * sizeof(one_count_t *));
    if (c->valueArr == NULL) {
      perror("fail to allocate memory for oneCount row");
      exit(EXIT_FAILURE);
    }
    /*
    one_count_t * oneCount = malloc(sizeof(*oneCount));
    if (oneCount == NULL) {
      perror("fail to allocate memory for oneCount struct");
      exit(EXIT_FAILURE);
    }

    oneCount->valueNum = 1;
    oneCount->value = malloc((strlen(name) + 1) * sizeof(char));
    if (oneCount->value == NULL) {
      perror("fail to allocate memory for the value");
      exit(EXIT_FAILURE);
    }
    */
    c->valueArr[c->size_valueArr - 1] = malloc(sizeof(one_count_t));
    c->valueArr[c->size_valueArr - 1]->value = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(c->valueArr[c->size_valueArr - 1]->value, name);
    c->valueArr[c->size_valueArr - 1]->valueNum = 1;
    // strcpy(oneCount->value, name);
    //c->valueArr[c->size_valueArr - 1] = oneCount;
  }

  /*
  if (unkown->valueNum != 0) {
    c->size_valueArr++;
    c->valueArr = realloc(c->valueArr, c->size_valueArr * sizeof(one_count_t *));
    c->valueArr[c->size_valueArr - 1] = unkown;
  }
  */
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  int hasUnknown = 0;
  int unknownNum = 0;
  for (int i = 0; i < c->size_valueArr; i++) {
    if (!(strcmp(c->valueArr[i]->value, "unknown"))) {
      hasUnknown = 1;
      unknownNum = c->valueArr[i]->valueNum;
    }
    else {
      fprintf(outFile, "%s: %d\n", c->valueArr[i]->value, c->valueArr[i]->valueNum);
    }
  }
  if (hasUnknown) {
    fprintf(outFile, "<unknown> : %d\n", unknownNum);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->size_valueArr; i++) {
    free(c->valueArr[i]->value);
    free(c->valueArr[i]);
  }
  free(c->valueArr);
  free(c);
}
