
#include "rand_story.h"

#include <string.h>
int isPositiveInteger(const char * category_name) {
  if ((!category_name) || (*category_name == '\0') || (*category_name == '0')) {
    return 0;
  }
  while (*category_name) {
    if (!isdigit(*category_name)) {
      return 0;
    }
    category_name++;
  }
  return 1;
}
char * usePreviousWords(size_t index, category_t * usedWords) {
  // size_t index = atoi(category_name);
  //  if (index > usedWords->n_words) {
  // perror("the index is out of range!");
  //free(remainning);
  //free(category_name);
  // exit(EXIT_FAILURE);
  // }

  char * replace_word = usedWords->words[usedWords->n_words - index];
  return replace_word;
}

void freeUsedWords(category_t * usedWords) {
  for (size_t i = 0; i < usedWords->n_words; i++) {
    free(usedWords->words[i]);
  }
  free(usedWords->words);
  free(usedWords);
}
char ** getNewStory(char * filename, catarray_t * myCatarray, int * lineNum) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("could not open the file!");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t sz = 0;
  char ** story = NULL;
  ssize_t lineLen = 0;
  category_t * usedWords = malloc(sizeof(*usedWords));
  usedWords->words = NULL;
  usedWords->n_words = 0;
  usedWords->name = NULL;

  while ((lineLen = getline(&line, &sz, f)) > 0) {
    //    story = realloc(story, (lineNum + 1) * sizeof(*story));
    // story[lineNum] = malloc((lineLen + 1) * sizeof(char));
    //lineNum++;
    char * category_name = NULL;
    char * first_dilimeter = NULL;
    // category_t * usedWords = malloc(sizeof(*usedWords));
    // usedWords->words = NULL;
    // usedWords->n_words = 0;
    // usedWords->name = NULL;
    while ((first_dilimeter = strchr(line, '_')) != NULL) {
      char * second_dilimeter = NULL;
      second_dilimeter = strchr(first_dilimeter + 1, '_');
      if (second_dilimeter == NULL) {
        perror("missing the second '_'\n");
        exit(EXIT_FAILURE);
      }
      char * remainning = strdup(second_dilimeter + 1);
      second_dilimeter[0] = '\0';
      category_name = strdup(first_dilimeter + 1);
      char * replace_word = NULL;
      //    if (isStep1) {
      //  replace_word = chooseWord(category_name, NULL);
      // }
      //check whether category_name is a real number.
      story = realloc(story, ((*lineNum) + 1) * sizeof(*story));
      story[*lineNum] = NULL;
      if (isPositiveInteger(category_name)) {
        size_t index = atoi(category_name);
        if (index > usedWords->n_words) {
          perror("the index is out of range!");
          free(remainning);
          free(category_name);
          freeUsedWords(usedWords);
          freeCatarry(myCatarray);
          free(line);
          freeStory(story, *lineNum);
          if (fclose(f) != 0) {
            perror("could not close the file!");
          }
          exit(EXIT_FAILURE);
        }

        replace_word = usePreviousWords(index, usedWords);
      }
      else {
        replace_word = (char *)chooseWord(category_name, myCatarray);
      }
      usedWords->words =
          realloc(usedWords->words, (usedWords->n_words + 1) * sizeof(char *));
      usedWords->words[usedWords->n_words] =
          malloc((strlen(replace_word) + 1) * sizeof(char));
      strcpy(usedWords->words[usedWords->n_words], replace_word);
      usedWords->n_words++;

      first_dilimeter[0] = '\0';
      //  line = realloc(
      //   line,
      //   (strlen(line) + strlen(replace_word) + strlen(remainning) + 1) * sizeof(char));
      strcat(line, replace_word);
      strcat(line, remainning);
      free(remainning);
      free(category_name);
      // if (isPositiveInteger(category_name)) {
      //      free(replace_word);
      //}
      //      free(replace_word);
    }
    //    free(category_name);
    // story = realloc(story, ((*lineNum) + 1) * sizeof(*story));
    //story[*lineNum] = malloc((lineLen + 1) * sizeof(char));
    story[*lineNum] = strdup(line);
    //strcpy(story[*lineNum], line);
    (*lineNum)++;
    // printf("%s", line);
  }

  free(line);

  freeUsedWords(usedWords);
  if (fclose(f) != 0) {
    perror("could not close the file!");
    exit(EXIT_FAILURE);
  }
  return story;
}

void printStory(char ** story, int lineNum) {
  for (int i = 0; i < lineNum; i++) {
    printf("%s", story[i]);
  }
}

void freeStory(char ** story, int lineNum) {
  for (int i = 0; i < lineNum; i++) {
    free(story[i]);
  }
  free(story);
}
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

void readCat(catarray_t * myCatarray, char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("could not open the file!");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;

  size_t sz = 0;
  while (getline(&line, &sz, f) != -1) {
    parseCat(line, myCatarray);
  }

  free(line);
  if (fclose(f) != 0) {
    perror("could not close the file!");
    exit(EXIT_FAILURE);
  }
}
void freeCatarry(catarray_t * myCat) {
  for (size_t i = 0; i < myCat->n; i++) {
    for (size_t j = 0; j < myCat->arr[i].n_words; j++) {
      free(myCat->arr[i].words[j]);
    }
    free(myCat->arr[i].name);
    free(myCat->arr[i].words);
  }
  free(myCat->arr);
  free(myCat);
}
