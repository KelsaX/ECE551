#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
class Page {
 public:
  enum Type { N, W, L };

  Page() : type(N) {}

  void setType(Type t) { type = t; }
  void addChoice(const std::string & choice) { choices.push_back(choice); }
  void adddestPages(size_t destPageNum) { destPages.push_back(destPageNum); }
  void loadFromText(const std::string & text);
  void display(std::vector<int> unvailableChoices) const;
  Type getType() const { return type; }
  std::vector<std::string> getChoices();
  size_t getdestPageNum(size_t choice);
  void addConditions(const std::string & condition, int choiceNum) {
    conditions[choiceNum] = condition;
  }
  void addVariables(const std::string variableName, int value) {
    variables[variableName] = value;
  }
  void updateStoryVariables(std::map<std::string, int> & storyVariables);
  void parseCondition(const std::string & condition);
  std::map<int, std::string> getConditions() { return conditions; }
  bool isChoiceAvailable(const std::vector<int> & unavailableChoices,
                         int currentChoice) const;

 private:
  Type type;
  std::vector<std::string> choices;
  std::vector<size_t> destPages;
  std::map<int, std::string> conditions;
  std::map<std::string, int> variables;
  std::string text;
};

bool Page::isChoiceAvailable(const std::vector<int> & unavailableChoices,
                             int currentChoice) const {
  return std::find(unavailableChoices.begin(), unavailableChoices.end(), currentChoice) ==
         unavailableChoices.end();
}
void Page::updateStoryVariables(std::map<std::string, int> & storyVariables) {
  for (std::map<std::string, int>::const_iterator it = variables.begin();
       it != variables.end();
       ++it) {
    storyVariables[it->first] = it->second;
  }
}
size_t Page::getdestPageNum(size_t choice) {
  return destPages[choice - 1];
}
std::vector<std::string> Page::getChoices() {
  return choices;
}
void Page::loadFromText(const std::string & text) {
  this->text = text;
}

void Page::display(std::vector<int> unvailableChoices) const {
  //  std::cout << "Page " << pageNum << "\n==========\n";
  std::cout << text << "\n";

  if (type == N && !choices.empty()) {
    std::cout << "What would you like to do?\n";
    for (size_t i = 0; i < choices.size(); ++i) {
      if (isChoiceAvailable(unvailableChoices, i + 1)) {
        std::cout << "\n " << (i + 1) << ". " << choices[i];
      }
      else {
        std::cout << "\n " << (i + 1) << ". "
                  << "<UNAVAILABLE>";
      }
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
