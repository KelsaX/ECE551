
#include "rand_story.h"

#include <string.h>

// Function to check if a given string represents a positive integer.
int isPositiveInteger(const char * category_name) {
  // Check if the pointer is NULL, string is empty, or starts with '0'.
  // These conditions mean it is not a positive integer.
  if ((!category_name) || (*category_name == '\0') || (*category_name == '0')) {
    return 0;  // Return 0 (false) if any of the above conditions are true.
  }
  while (*category_name) {
    if (!isdigit(*category_name)) {
      return 0;  // If the current character is not a digit, return 0 (false).
    }
    category_name++;
  }
  // If all characters were digits and we didn't start with '0',
  // the string represents a positive integer, so return 1 (true).
  return 1;
}

// Function to retrieve a word previously used in the story.
// 'index' specifies how far back in the list of used words to go.
// 'usedWords' is a pointer to a category_t struct that contains an array of words and the count of words.
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

/* Function to delete a word from a category in a category array.
 */
void deleteUsed(catarray_t * myCatarray, char * replace_word, char * category_name) {
  // Initialize indices to represent an invalid position
  size_t index_arr = -1;
  size_t index_word = -1;
  // Iterate over each category in the category array
  // printf("delete");
  for (size_t i = 0; i < myCatarray->n; i++) {
    // Check if the current category name matches the one we're looking for
    if (strcmp(category_name, myCatarray->arr[i].name) == 0) {
      index_arr = i;  // If it matches, store the index of this category

      // Iterate over each word in the category's word list
      for (size_t j = 0; j < myCatarray->arr[i].n_words; j++) {
        // Check if the current word matches the one we want to replace
        if (strcmp(myCatarray->arr[i].words[j], replace_word) == 0) {
          index_word = j;  // If it matches, store the index of this word
          //      char * replace_word2 = strdup(myCatarray->arr[i].words[j]);
          // replace_word = replace_word2;
          //          printf("the name index is %ld, and the word index is %ld\n",
          //     index_arr,
          //     index_word);
          break;  // Break the loop since we found the word
        }
      }
      break;  // Break the loop since we found the category
    }
  }
  // Check if valid indices were found
  if (index_arr >= 0 && index_word >= 0) {
    //free(myCatarray->arr[index_arr].words[index_word]);
    // char * tobeDelete = myCatarray->arr[index_arr].words[index_word];
    //  printf("prepare to delete");
    // Move the last word in the category to the position of the word to delete
    // myCatarray->arr[index_arr].words[index_word] =
    //  myCatarray->arr[index_arr].words[myCatarray->arr[index_arr].n_words - 1];

    // Shift all words after the deleted word one position to the left to fill the gap
    for (size_t m = index_word; m < (myCatarray->arr[index_arr].n_words - 1); m++) {
      //printf("before the movw");
      myCatarray->arr[index_arr].words[m] = myCatarray->arr[index_arr].words[m + 1];
      // printf("move: %ld", m);
    }
    //  myCatarray->arr[index_arr].words[myCatarray->arr[index_arr].n_words - 1] = tobeDelete;
    //free(myCatarray->arr[index_arr].words[myCatarray->arr[index_arr].n_words - 1]);
    // myCatarray->arr[index_arr].words =
    //  realloc(myCatarray->arr[index_arr].words,
    //          (myCatarray->arr[index_arr].n_words - 1) * sizeof(char *));
    //    free(tobeDelete);  //  printf("delete completw!!!");
    // Decrease the word count for the category after the deletion
    myCatarray->arr[index_arr].n_words--;
    //    printf("%s", replace_word);
  }
  else {
    // If no valid index was found, print an error message

    printf("somethinf wrong!");
  }
}

//the function is to free usedWords.
void freeUsedWords(category_t * usedWords) {
  for (size_t i = 0; i < usedWords->n_words; i++) {
    free(usedWords->words[i]);
  }
  free(usedWords->words);
  free(usedWords);
}

// Define a function to read a story template from a file and replace placeholders
// with words from categories.
char ** getNewStory(char * filename,
                    catarray_t * myCatarray,
                    int * lineNum,
                    int reusable) {
  // Open the file for reading.
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("could not open the file!");
    exit(EXIT_FAILURE);
  }
  // Initialize variables to hold each line of the file, its size, the final story,
  // and the length of each line.
  char * line = NULL;
  size_t sz = 0;
  char ** story = NULL;
  ssize_t lineLen = 0;
  // Allocate memory for tracking used words.
  category_t * usedWords = malloc(sizeof(*usedWords));
  usedWords->words = NULL;
  usedWords->n_words = 0;
  usedWords->name = NULL;
  // Read the file line by line.
  while ((lineLen = getline(&line, &sz, f)) > 0) {
    //    story = realloc(story, (lineNum + 1) * sizeof(*story));
    // story[lineNum] = malloc((lineLen + 1) * sizeof(char));
    //lineNum++;

    // Find the first underscore which indicates the start of a placeholder.
    char * category_name = NULL;
    char * first_dilimeter = NULL;
    // int freeWord = 0;
    // category_t * usedWords = malloc(sizeof(*usedWords));
    // usedWords->words = NULL;
    // usedWords->n_words = 0;
    // usedWords->name = NULL;
    while ((first_dilimeter = strchr(line, '_')) != NULL) {
      // Flag for whether the replace_word should be freed.
      int freeWord = 0;
      // Find the second underscore which indicates the end of a placeholder.
      char * second_dilimeter = NULL;

      second_dilimeter = strchr(first_dilimeter + 1, '_');
      // If second underscore is not found, print an error and exit.
      if (second_dilimeter == NULL) {
        perror("missing the second '_'\n");
        exit(EXIT_FAILURE);
      }
      // Duplicate the remaining string after the second delimiter for later use.
      char * remainning = strdup(second_dilimeter + 1);
      // Terminate the category part to isolate it.
      second_dilimeter[0] = '\0';
      // Duplicate the category name from the string.
      category_name = strdup(first_dilimeter + 1);
      char * replace_word = NULL;
      //    if (isStep1) {
      //  replace_word = chooseWord(category_name, NULL);
      // }

      // Reallocate memory for the story array to hold one more line.
      story = realloc(story, ((*lineNum) + 1) * sizeof(*story));
      story[*lineNum] = NULL;
      // If the category name is an integer, use it to index into the used words.
      if (isPositiveInteger(category_name)) {
        size_t index = atoi(category_name);
        // If the index is out of range, print an error and exit.
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
        // Retrieve the word used at the specified index.
        replace_word = usePreviousWords(index, usedWords);
      }
      else {
        // Otherwise, choose a word from the category array.
        replace_word = (char *)chooseWord(category_name, myCatarray);
        // If the word is not reusable, remove it from the category array.
        if (!reusable) {
          deleteUsed(myCatarray, replace_word, category_name);
          // Set the flag to free the replace_word later.
          freeWord = 1;
        }
      }
      //      printf("%s\n", replace_word);
      // Reallocate the usedWords to store the new word.
      usedWords->words =
          realloc(usedWords->words, (usedWords->n_words + 1) * sizeof(char *));
      // Allocate space for the new word and copy it into the usedWords array.
      usedWords->words[usedWords->n_words] =
          malloc((strlen(replace_word) + 1) * sizeof(char));
      strcpy(usedWords->words[usedWords->n_words], replace_word);
      usedWords->n_words++;
      // Restore the original line with the replaced word and the remaining string.
      first_dilimeter[0] = '\0';
      //  line = realloc(
      //   line,
      //   (strlen(line) + strlen(replace_word) + strlen(remainning) + 1) * sizeof(char));
      strcat(line, replace_word);
      strcat(line, remainning);
      free(remainning);
      // free(category_name);
      // if (isPositiveInteger(category_name)) {
      //      free(replace_word);
      //}
      //      if (!reusable) {
      //  deleteUsed(myCatarray, replace_word, category_name);

      // }  //      free(replace_word);
      // free(category_name);

      // If needed, free the replaced word.
      if (freeWord) {
        free(replace_word);
        // deleteUsed(myCatarray, replace_word, category_name);
      }
      free(category_name);
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

//the function is to print out the story
void printStory(char ** story, int lineNum) {
  for (int i = 0; i < lineNum; i++) {
    printf("%s", story[i]);
  }
}
//the function is to free story.
void freeStory(char ** story, int lineNum) {
  for (int i = 0; i < lineNum; i++) {
    free(story[i]);
  }
  free(story);
}

// Function to look up a category by its name and add a new word to the category.
int lookUpCat(const char * name, char * newWord, catarray_t * myCatarray) {
  for (size_t i = 0; i < myCatarray->n; i++) {
    // Check if the current category name matches the one we're looking for.
    if (strcmp(name, myCatarray->arr[i].name) == 0) {
      myCatarray->arr[i].words = realloc(
          myCatarray->arr[i].words, (myCatarray->arr[i].n_words + 1) * sizeof(char *));
      myCatarray->arr[i].words[myCatarray->arr[i].n_words] =
          malloc((strlen(newWord) + 1) * sizeof(char));
      // Copy the new word into the newly allocated space.
      strcpy(myCatarray->arr[i].words[myCatarray->arr[i].n_words], newWord);

      myCatarray->arr[i].n_words++;
      // Return 1 to indicate the word was successfully added.
      return 1;
    }
  }
  // If the category name was not found, return 0.
  return 0;
}

// Function to parse a category from a line and add it to a catarray_t structure.
void parseCat(char * line, catarray_t * myCatarray) {
  // Find the first occurrence of ':' which is used to separate the category name and words.
  char * dilimeter = strchr(line, ':');
  char * wordStart = dilimeter + 1;
  int lineLen = strlen(line);
  char * lineEnd = line + lineLen - 1;
  lineEnd[0] = '\0';
  if (dilimeter == NULL) {
    perror("there is no : in the line!");
    // If there is no ':' in the line, print an error message and exit.
    exit(EXIT_FAILURE);
  }
  // Use strtok to get the category name which is before the ':' delimiter.
  //char * newName = strtok(line, ":");
  dilimeter[0] = '\0';
  char * newName = line;
  //char * newName = strdup(line);
  // Use strtok to get the following word(s), after the ':' delimiter and before the newline.
  if (strcmp(newName, ":") == 0) {
    perror("the catogory name is in a wrong format!");
    exit(EXIT_FAILURE);
  }
  char * newWord = wordStart;
  // char * newWord = strtok(NULL, "\n");

  if (strcmp(newWord, ":") == 0) {
    perror("the catogory word is in a wrong format!");
    exit(EXIT_FAILURE);
  }

  // If the category doesn't already exist, add a new category to myCatarray.
  if (!lookUpCat(newName, newWord, myCatarray)) {
    // Reallocate memory for the array within myCatarray to accommodate the new category.
    // This is done by increasing the size by one category_t struct.
    myCatarray->arr = realloc(myCatarray->arr, (myCatarray->n + 1) * sizeof(category_t));
    // If realloc fails, print an error message and exit.
    if (myCatarray->arr == NULL) {
      perror("fail to allocate memory for one category name!");
      exit(EXIT_FAILURE);
    }
    // Allocate memory for the new category name and store it in the array.
    myCatarray->arr[myCatarray->n].name = malloc((strlen(newName) + 1) * sizeof(char));
    // Copy the new category name into the newly allocated memory.
    strcpy(myCatarray->arr[myCatarray->n].name, newName);
    // Allocate memory for a new words pointer within the category.

    myCatarray->arr[myCatarray->n].words = malloc(sizeof(char *));
    // Initialize the number of words for this category to 1.

    myCatarray->arr[myCatarray->n].n_words = 1;
    // Allocate memory for the new word and store it in the words array within the category.
    myCatarray->arr[myCatarray->n].words[0] =
        malloc((strlen(newWord) + 1) * sizeof(char));
    // Copy the new word into the newly allocated memory.
    strcpy(myCatarray->arr[myCatarray->n].words[0], newWord);

    myCatarray->n++;
  }
}
// Define a function to read categories from a file and populate a catarray_t
void readCat(catarray_t * myCatarray, char * filename) {
  // Attempt to open the file with the provided filename in read mode.
  FILE * f = fopen(filename, "r");
  // If fopen returns NULL, the file couldn't be opened; report this error and exit.
  if (f == NULL) {
    perror("could not open the file!");
    exit(EXIT_FAILURE);
  }
  // Declare a pointer for reading lines from the file, initializing it to NULL.
  char * line = NULL;
  // Declare a size_t variable to hold the size of the allocated buffer for getline.
  size_t sz = 0;
  // Read the file line by line using getline.
  while (getline(&line, &sz, f) != -1) {
    // For each line, parse the category data and add it to the catarray_t structure.
    parseCat(line, myCatarray);
  }
  // After all lines are read and processed, free the line buffer allocated by getline.
  free(line);
  // Close the file and check for errors in closing.
  if (fclose(f) != 0) {
    // If fclose returns a non-zero value, there was an error closing the file.
    perror("could not close the file!");
    exit(EXIT_FAILURE);
  }
}

// Define a function to free all the memory associated with a catarray_t structure.
void freeCatarry(catarray_t * myCat) {
  // Iterate over each category in the catarray_t structure.
  for (size_t i = 0; i < myCat->n; i++) {
    // For each category, iterate over all words and free each word.
    for (size_t j = 0; j < myCat->arr[i].n_words; j++) {
      free(myCat->arr[i].words[j]);
    }
    // Free the memory for the name of the category.
    free(myCat->arr[i].name);
    // Free the memory for the array of words in the category.
    free(myCat->arr[i].words);
  }
  // Free the memory for the array of categories.
  free(myCat->arr);
  // Finally, free the catarray_t structure itself.
  free(myCat);
}
