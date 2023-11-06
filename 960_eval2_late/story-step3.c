#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 3) {
    perror("the command argument are wrong!");
    return EXIT_FAILURE;
  }
  catarray_t * myCatarray = malloc(sizeof(*myCatarray));
  myCatarray->arr = NULL;
  myCatarray->n = 0;
  readCat(myCatarray, argv[1]);  //store the name and words in myCatarray
  int lineNum = 0;
  char ** story = getNewStory(
      argv[2], myCatarray, &lineNum, 1);  //read the story and get the new story
  printStory(story, lineNum);
  freeStory(story, lineNum);
  freeCatarry(myCatarray);

  return EXIT_SUCCESS;
}
