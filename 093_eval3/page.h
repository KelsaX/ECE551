#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Page {
 public:
  enum Type { N, W, L };

  Page() : type(N) {}

  void setType(Type t) { type = t; }
  void addChoice(const std::string & choice) { choices.push_back(choice); }
  void loadFromText(const std::string & text);
  void display(int pageNum) const;

  Type getType() const { return type; }

 private:
  Type type;
  std::vector<std::string> choices;
  std::string text;
};

void Page::loadFromText(const std::string & text) {
  this->text = text;
}

void Page::display(int pageNum) const {
  std::cout << "Page " << pageNum << "\n==========\n";
  std::cout << text << "\n";

  if (type == N && !choices.empty()) {
    std::cout << "What would you like to do?\n";
    for (size_t i = 0; i < choices.size(); ++i) {
      std::cout << "\n " << (i + 1) << ". " << choices[i];
    }
  }
  else if (type == W) {
    std::cout << "Congratulations! You have won. Hooray!";
  }
  else if (type == L) {
    std::cout << "Sorry, you have lost. Better luck next time!";
  }
  else {
    std::ostringstream errorStr;
    errorStr << "the page type is wrong in page.h!";
    throw std::runtime_error(errorStr.str());
  }
  std::cout << "\n";
}
