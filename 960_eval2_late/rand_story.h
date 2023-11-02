#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use
void freeUsedWords(category_t * usedWords);
char ** getNewStory(char * filename, catarray_t * myCatarray, int * lineNum);
void printStory(char ** story, int lineNum);
void freeStory(char ** story, int lineNum);
int lookUpCat(const char * name, char * newWord, catarray_t * myCatarray);
void parseCat(char * line, catarray_t * myCatarray);
void readCat(catarray_t * myCatarray, char * filename);
void freeCatarry(catarray_t * myCat);
char * usePreviousWords(size_t index, category_t * usedWords);
int isPositiveInteger(const char * category_name);
#endif
