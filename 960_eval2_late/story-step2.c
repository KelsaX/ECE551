#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

int lookUpCat(const char * name, char * newWord, catarray_t * myCatarray) {
  for (size_t i = 0; i < myCatarray->n; i++) {
    if (strcmp(name, myCatarray->arr[i].name) == 0) {
      myCatarray->arr[i].words = realloc(
          myCatarray->arr[i].words, (myCatarray->arr[i].n_words + 1) * sizeof(char *));
      myCatarray->arr[i].words[myCatarray->arr[i].n_words] =
          malloc((strlen(newWord) + 1) * sizeof(char));

      strcpy(myCatarray->arr[i].words[myCatarray->arr[i].n_words], newWord);

      myCatarray->arr[i].n_words++;

      return 1;
    }
  }
  return 0;
}
void parseCat(char * line, catarray_t * myCatarray) {
  char * dilimeter = strchr(line, ':');
  if (dilimeter == NULL) {
    perror("there is no : in the line!");
    exit(EXIT_FAILURE);
  }
  char * newName = strtok(line, ":");
  char * newWord = strtok(NULL, "\n");
  if (!lookUpCat(newName, newWord, myCatarray)) {
    myCatarray->arr = realloc(myCatarray->arr, (myCatarray->n + 1) * sizeof(category_t));
    //myCatarray->n++;
    if (myCatarray->arr == NULL) {
      perror("fail to allocate memory for one category name!");
      exit(EXIT_FAILURE);
    }
    myCatarray->arr[myCatarray->n].name = malloc((strlen(newName) + 1) * sizeof(char));
    strcpy(myCatarray->arr[myCatarray->n].name, newName);

    myCatarray->arr[myCatarray->n].words = malloc(sizeof(char *));
    myCatarray->arr[myCatarray->n].n_words = 1;

    myCatarray->arr[myCatarray->n].words[0] =
        malloc((strlen(newWord) + 1) * sizeof(char));
    strcpy(myCatarray->arr[myCatarray->n].words[0], newWord);
    myCatarray->n++;
  }
}
void readCat(catarray_t * myCatarray, FILE * f) {
  char * line = NULL;

  size_t sz = 0;
  while (getline(&line, &sz, f) != -1) {
    parseCat(line, myCatarray);
  }

  free(line);
}
void freeCatarry(catarray_t * myCat) {
  for (size_t i = 0; i < myCat->n; i++) {
    for (size_t j = 0; j < myCat->arr[i].n_words; j++) {
      free(myCat->arr[i].words[j]);
    }
    free(myCat->arr[i].name);
    free(myCat->arr[i].words);
    //free(myCat->arr);
  }
  free(myCat->arr);
  free(myCat);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    perror("the command argument is wrong!");
    return (EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("could not open the file!");
    return (EXIT_FAILURE);
  }
  catarray_t * myCatarray = malloc(sizeof(*myCatarray));
  myCatarray->arr = NULL;
  myCatarray->n = 0;
  readCat(myCatarray, f);
  printWords(myCatarray);
  freeCatarry(myCatarray);
  if (fclose(f) != 0) {
    perror("could not close the file!");
    return (EXIT_FAILURE);
  }

  return (EXIT_SUCCESS);
}
