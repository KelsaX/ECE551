#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

void printNewStory(FILE * f) {
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) > 0) {
    // char * token = NULL;
    char * category_name = NULL;
    char * first_dilimeter = NULL;
    // token = strtok(line, "_");
    //while((token = strtok(NULL, "_"))!=NULL){
    while ((first_dilimeter = strchr(line, '_')) != NULL) {
      //  int beginingLen=first_dilimeter-line;
      char * second_dilimeter = NULL;
      second_dilimeter = strchr(first_dilimeter + 1, '_');
      if (second_dilimeter == NULL) {
        perror("missing the second '_'\n");
        exit(EXIT_FAILURE);
      }
      char * remainning = strdup(second_dilimeter + 1);
      //  printf("%s", remainning);
      second_dilimeter[0] = '\0';
      //category_name = strtok(first_dilimeter, "_");
      category_name = strdup(first_dilimeter + 1);
      //   printf("%s", category_name);
      const char * replace_word = chooseWord(category_name, NULL);
      //int category_name_len = strlen(category_name);
      first_dilimeter[0] = '\0';
      strcat(line, replace_word);
      strcat(line, remainning);
      free(remainning);
      free(category_name);
      //      printf("%s", line);

      /*
      int beginingLen = 0;
      if (line[0] == '_') {
        token = NULL;
        category_name = strtok(line, "_");
      }
      else {
        token = strtok(line, "_");
        beginingLen = strlen(token);
        category_name = strtok(NULL, "_");
      }
      //      printf("%s", category_name);
      if (category_name == NULL) {
        perror("missing the second ’_'");
        exit(EXIT_FAILURE);
      }
      const char * replace_word = chooseWord(category_name, NULL);

      int category_name_len = strlen(category_name);
      if (token == NULL) {
        char * newline = strdup(replace_word);
        strcat(newline, line + beginingLen + category_name_len + 2);
        line = newline;
      }
      else {
        strcat(token, replace_word);
        strcat(token, line + beginingLen + category_name_len + 2);
        line = token;
      }
      // printf("%s", token);
      //printf("%s", replac f5e_word);
      //  printf("%s", line);
    }
}
      */
      //char* remaining=strtok(NULL,"\n");
    }
    printf("%s", line);
  }
  free(line);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    perror("the argument is wrong!");
    return (EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("could not open the file!");
    return (EXIT_FAILURE);
  }
  printNewStory(f);
  if (fclose(f) != 0) {
    perror("could not close the file!");
    return (EXIT_FAILURE);
  }

  return (EXIT_SUCCESS);
}
