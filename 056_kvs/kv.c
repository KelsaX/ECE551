#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t * parseKv(char * line) {
  char * newKey = strtok(line, "=");
  if (newKey == NULL) {
    perror("there is no = in the pair!");
    exit(EXIT_FAILURE);
  }
  char * newValue = strtok(NULL, "\n");
  /*
    char* newValuestrchr(line, '=')+1;
    char* newkey=
   */
  kvpair_t * pair = malloc(sizeof(kvpair_t));
  pair->key = malloc((strlen(newKey) + 1) * sizeof(char));
  pair->value = malloc((strlen(newValue) + 1) * sizeof(char));
  /*
  kv->kvArr = realloc(kv->kvArr, (kv->size_kv + 1) * sizeof(kvpair_t *));
  if (kv->kvArr == NULL) {
    perror("fail to reallocate memory for kvpair row");
    exit(EXIT_FAILURE);
  }
  kv->kvArr[kv->size_kv] = malloc(sizeof(kvpair_t));
  */
  if (pair == NULL) {
    perror("fail to malloc memory for kvpair!");
    exit(EXIT_FAILURE);
  }
  strcpy(pair->key, newKey);
  strcpy(pair->value, newValue);
  return pair;
}
/*
void stripNewline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}
*/
void readOne(kvarray_t * kv, FILE * f) {
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) != -1) {
    //  stripNewline(line);
    kv->kvArr = realloc(kv->kvArr, (kv->size_kv + 1) * sizeof(kvpair_t *));
    if (kv->kvArr == NULL) {
      perror("fail to reallocate memory for kvpair row!");
      exit(EXIT_FAILURE);
    }

    kv->kvArr[kv->size_kv] = parseKv(line);

    kv->size_kv++;
  }
  free(line);
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("could not open the file!");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kv = malloc(sizeof(*kv));
  kv->size_kv = 0;
  kv->kvArr = NULL;
  readOne(kv, f);
  if (fclose(f) != 0) {
    perror("could not close the file!");
    exit(EXIT_FAILURE);
  }
  return kv;
}
void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->size_kv; i++) {
    free(pairs->kvArr[i]->key);
    free(pairs->kvArr[i]->value);
    free(pairs->kvArr[i]);
  }
  free(pairs->kvArr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->size_kv; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvArr[i]->key, pairs->kvArr[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->size_kv; i++) {
    if (strcmp(pairs->kvArr[i]->key, key) == 0) {
      return pairs->kvArr[i]->value;
    }
  }
  return NULL;
}
