#include "story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    //  std::ostringstream errorStr;
    // errorStr << "the program arguments should be 2";
    // throw std::runtime_error(errorStr.str());
    std::cerr << "the program arguments should be 2\n";
    return (EXIT_FAILURE);
  }
  try {
    Story story;
    story.loadFromDirectory(argv[1]);
    //  story.findWinningPaths();
    story.storyStart();
  }
  catch (const std::exception & e) {
    std::cerr << "Error: " << e.what() << "\n";
    return (EXIT_FAILURE);
  }

  return (EXIT_SUCCESS);
}
