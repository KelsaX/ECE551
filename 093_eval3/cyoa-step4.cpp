#include "story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "the number of the program arguments should be 2!\n";
    return (EXIT_FAILURE);
  }
  try {
    Story story;
    story.loadFromDirectory(argv[1]);
    story.storyStart();
  }
  catch (const std::exception & e) {
    std::cerr << "Error: " << e.what() << "\n";

    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
