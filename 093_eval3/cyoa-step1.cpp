#include "story.h"
int main(int argc, char * argv[]) {
  // Checks if the correct number of command-line arguments is provided.
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <directory>\n";
    return 1;
  }
  // Enclosing the main logic in a try-catch block to handle any exceptions.
  try {
    Story story;
    story.loadFromDirectory(argv[1]);
    story.display();
  }
  // Catches and handles any standard exceptions that may have been thrown.
  catch (const std::exception & e) {
    // Prints the error message to the standard error stream.
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
