#include "story.h"
int main(int argc, char ** argv) {
  // Checks if the correct number of command-line arguments is provided.
  if (argc != 2) {
    std::cerr << "the number of the program arguments should be 2!\n";
    return (EXIT_FAILURE);
  }
  // Enclosing the main logic in a try-catch block to handle any exceptions.
  try {
    Story story;
    story.loadFromDirectory(argv[1]);
    story.storyStart();
  }
  // Catches and handles any standard exceptions that may have been thrown.
  catch (const std::exception & e) {
    std::cerr << "Error: " << e.what() << "\n";

    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
