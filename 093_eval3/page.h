#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
// Class representing a single page in an interactive story.
class Page {
 public:
  // Enum to represent the type of the page. N for normal, W for winning, L for losing.
  enum Type { N, W, L };
  // Constructor initializes the page with a default type of 'Normal'.
  Page() : type(N) {}
  // Sets the type of the page.
  void setType(Type t) { type = t; }
  // Adds a choice (string) to the page.

  void addChoice(const std::string & choice) { choices.push_back(choice); }
  // Associates a destination page number with each choice.
  void adddestPages(size_t destPageNum) { destPages.push_back(destPageNum); }
  // Loads the content of the page from a text string.
  void loadFromText(const std::string & text);
  // Displays the content of the page, considering any unavailable choices.
  void display(std::vector<int> unvailableChoices) const;
  // Returns the type of the page.
  Type getType() const { return type; }
  // Returns a vector of all the choices on the page.
  std::vector<std::string> getChoices();
  // Returns the destination page number for a given choice.
  size_t getdestPageNum(size_t choice);
  // Adds a condition for a specific choice number.

  void addConditions(const std::string & condition, int choiceNum) {
    conditions[choiceNum] = condition;
  }
  // Adds or updates a variable on the page.
  void addVariables(const std::string variableName, int value) {
    variables[variableName] = value;
  }
  // Updates the story variables based on the variables defined on the page.
  void updateStoryVariables(std::map<std::string, int> & storyVariables);
  // Parses a condition string to determine its validity and meaning.
  void parseCondition(const std::string & condition);
  // Returns the conditions associated with choices on the page.
  std::map<int, std::string> getConditions() { return conditions; }
  // Determines if a specific choice is available, considering unavailable choices.
  bool isChoiceAvailable(const std::vector<int> & unavailableChoices,
                         int currentChoice) const;
  // Get the total destpage number for error checking.
  std::vector<size_t> getTotalDestPages() const { return destPages; }

 private:
  // Type of the page (Normal, Winning, Losing).
  Type type;
  // Vector of strings representing choices available on the page.
  std::vector<std::string> choices;
  // Vector of page numbers, each corresponding to a destination for a choice.
  std::vector<size_t> destPages;
  // Maps choice numbers to conditions that must be met for the choice to be available.
  std::map<int, std::string> conditions;
  // Maps variable names to their values for the page.
  std::map<std::string, int> variables;
  // Text content of the page.
  std::string text;
};

// Checks if a specific choice is available on the page.
bool Page::isChoiceAvailable(const std::vector<int> & unavailableChoices,
                             int currentChoice) const {
  // Returns true if the current choice is not found in the list of unavailable choices.
  return std::find(unavailableChoices.begin(), unavailableChoices.end(), currentChoice) ==
         unavailableChoices.end();
}
// Updates the story-wide variables with the variables defined on this page.
void Page::updateStoryVariables(std::map<std::string, int> & storyVariables) {
  for (std::map<std::string, int>::const_iterator it = variables.begin();
       it != variables.end();
       ++it) {
    // Updates the story-wide variables with the page-specific variables.
    storyVariables[it->first] = it->second;
  }
}
// Retrieves the destination page number for a given choice.
size_t Page::getdestPageNum(size_t choice) {
  // Returns the destination page number associated with the choice.
  // 'choice - 1' is used because choices are 1-indexed but stored in a 0-indexed vector.
  return destPages[choice - 1];
}
// Returns a vector of all choices available on the page.
std::vector<std::string> Page::getChoices() {
  return choices;
}
// Loads the textual content of the page from a given string.
void Page::loadFromText(const std::string & text) {
  this->text = text;
}
// Displays the content of the page along with the available choices.
void Page::display(std::vector<int> unvailableChoices) const {
  //  std::cout << "Page " << pageNum << "\n==========\n";
  std::cout << text << "\n";
  // If the page is a normal page and has choices, it displays those choices.
  if (type == N && !choices.empty()) {
    std::cout << "What would you like to do?\n";
    for (size_t i = 0; i < choices.size(); ++i) {
      // Checks if the choice is available.
      if (isChoiceAvailable(unvailableChoices, i + 1)) {
        std::cout << "\n " << (i + 1) << ". " << choices[i];
      }
      else {
        // Indicates if the choice is unavailable.
        std::cout << "\n " << (i + 1) << ". "
                  << "<UNAVAILABLE>";
      }
    }
  }
  // If the page is a winning page, displays a winning message.
  else if (type == W) {
    if (choices.size() != 0 || destPages.size() != 0) {
      throw std::runtime_error("win page can not have choices!");
    }

    std::cout << "Congratulations! You have won. Hooray!";
  }
  // If the page is a losing page, displays a losing message.
  else if (type == L) {
    if (choices.size() != 0 || destPages.size() != 0) {
      throw std::runtime_error("Lose page can not have choices!");
    }
    std::cout << "Sorry, you have lost. Better luck next time!";
  }
  else {
    // Throws an error if the page type is unrecognized.
    std::ostringstream errorStr;
    errorStr << "the page type is wrong in page.h!";
    throw std::runtime_error(errorStr.str());
  }
  std::cout << "\n";
}
