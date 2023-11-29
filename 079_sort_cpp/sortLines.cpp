#include <iostream>
//sort() is included in algorithm
#include <algorithm>
#include <fstream>
#include <string>  //getline and string
#include <vector>
//vector用来存储读取到的string所以vector是一个string类型的

int main(int argc, char ** argv) {
  std::vector<std::string> lines;

  if (argc == 1) {
    std::string line;
    while (std::getline(std::cin, line)) {
      lines.push_back(line);
    }
    std::sort(lines.begin(), lines.end());
    std::vector<std::string>::iterator it = lines.begin();
    while (it != lines.end()) {
      std::cout << *it << std::endl;
      ++it;
    }
  }
  else if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      std::string line;
      std::ifstream file(argv[i]);
      if (!file) {
        std::cerr << "could not open the file:" << argv[i] << std::endl;
        return (EXIT_FAILURE);
      }
      while (std::getline(file, line)) {
        lines.push_back(line);
      }
      std::sort(lines.begin(), lines.end());
      std::vector<std::string>::iterator it = lines.begin();
      while (it != lines.end()) {
        std::cout << *it << std::endl;
        ++it;
      }

      lines.clear();
      file.close();
    }
  }

  return (EXIT_SUCCESS);
}
