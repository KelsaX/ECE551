#include "story.h"
int main(int argc, char * argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <directory>\n";
    return 1;
  }

  try {
    Story story;
    story.loadFromDirectory(argv[1]);
    story.display();
  }
  catch (const std::exception & e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
