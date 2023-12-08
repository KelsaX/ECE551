#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>

#include "page.h"
// Story class represents an interactive story. Each story consists of multiple pages.

class Story {
 public:
  // Constructor initializes the story with an expected first page number.
  Story() : nextExpectedPageNum(0) {}
  // Loads the story data from a specified directory.
  // Loads the story data from a specified directory. This includes parsing the story structure,
  // pages, choices, conditions, and variables from text files.
  void loadFromDirectory(const std::string & directory);
  // Displays the story content.
  void display() const;
  // Starts the interactive story session.
  void storyStart();
  // Finds and displays all the winning paths in the story.
  void findWinningPaths();

 private:
  std::map<size_t, Page> pages;    // Stores pages of the story indexed by page number.
  std::set<size_t> declaredPages;  // Tracks the declared pages.
  size_t nextExpectedPageNum;      // Next expected page number in sequence.
  std::map<std::string, int> variables;  // Stores variables used in the story.
  // std::string intToString(int num);
  // Validates the order of page declarations.
  void validatePageDeclarationOrder(size_t pageNum);
  // Adds a choice to a specific page.
  void addChoiceToPage(size_t pageNum,
                       size_t destPageNum,
                       const std::string & choiceText);
  // Parses a page declaration from a line of text.
  void parsePageDeclaration(const std::string & line, const std::string & directory);
  // Parses a choice line from the story data.
  void parseChoiceLine(const std::string & line);
  // Checks if a string represents a valid number and returns its value.
  size_t isValidNumber(const std::string & str);
  // void findWinningPaths();
  // Depth-first search to find all winning paths in the story.
  void dfsFindPath(std::vector<std::pair<size_t, int> > & path,
                   std::vector<std::vector<std::pair<size_t, int> > > & winningPaths,
                   size_t currentPageNum,
                   std::set<size_t> & visited);
  // Parses a variable assignment line from the story data.
  void parseVariableAssignment(const std::string & line);
  // bool isChoiceAvailable(int choice);
  // Checks if a given condition is satisfied based on the current story variables.
  bool isConditionSatisfied(const std::string & condition);
};

//std::string Story::intToString(int num) {
//  std::ostringstream ss;
//  ss << num;
//  return ss.str();
//}
//bool Story::isChoiceAvailable(int choice) {
// return true;
//}

// This function checks if a given condition in the story is satisfied. Conditions are typically used to determine
// whether certain choices in the story are available based on the current state of the story variables.

bool Story::isConditionSatisfied(const std::string & condition) {
  size_t equalPos = condition.find('=');

  // If the equals sign is not found, the condition string format is invalid,
  // and an exception is thrown.
  if (equalPos == std::string::npos) {
    throw std::runtime_error("Condition format error: " + condition);
  }
  // Extracts the variable name from the condition string. This is the substring
  // before the equals sign.
  std::string variableName = condition.substr(0, equalPos);
  // Extracts the expected value (as a number) from the condition string. This is the substring
  // after the equals sign. The function `isValidNumber` is used to convert the substring into an integer.
  int expectedValue = isValidNumber(condition.substr(equalPos + 1));
  std::map<std::string, int>::iterator it = variables.find(variableName);

  // If the variable is found in the map, it compares the variable's current value
  // with the expected value. If they match, the condition is satisfied (returns true).
  if (it != variables.end()) {
    return it->second == expectedValue;
  }
  return expectedValue == 0;
}
// This function parses a line from the story data to assign a value to a variable on a specific page.
void Story::parseVariableAssignment(const std::string & line) {
  std::istringstream lineStream(line);
  std::string pageToSet;
  std::getline(lineStream, pageToSet, '$');
  std::string variableAssignment;
  // Converts the extracted page number from text to a numeric value. The `isValidNumber` function
  // checks if the string represents a valid number and returns its value.
  size_t pageNum = isValidNumber(pageToSet);
  if (std::getline(lineStream, variableAssignment)) {
    size_t equalPos = variableAssignment.find('=');
    // If the equals sign is not found, the format of the variable assignment is invalid,
    // and an exception is thrown.
    if (equalPos == std::string::npos) {
      std::ostringstream errorStr;
      errorStr << "the variable assignment is not valid";
      throw std::runtime_error(errorStr.str());
    }
    std::string variableName = variableAssignment.substr(0, equalPos);
    std::string valueStr = variableAssignment.substr(equalPos + 1);
    int value = isValidNumber(valueStr);
    // variable[variableName] = value;
    // Adds the variable and its value to the specified page.
    // The `addVariables` method of the Page class is used to update the variable's value in the page.
    pages[pageNum].addVariables(variableName, value);
  }
  else {
    std::ostringstream errorStr;
    errorStr << "the format of the variable assignment line is not valid";
    throw std::runtime_error(errorStr.str());
  }
}

// This function finds and prints all the winning paths in the interactive story.
// A winning path is a sequence of choices leading to a winning page.
void Story::findWinningPaths() {
  // A path is represented as a vector of pairs, where each pair contains a page number and a choice number.
  // The choice number indicates which choice was made on that page.
  std::vector<std::pair<size_t, int> > path;
  // A vector to store all the winning paths found in the story.
  std::vector<std::vector<std::pair<size_t, int> > > winningPaths;
  // A set to keep track of visited pages during the search to avoid cycles.
  std::set<size_t> visited;

  // Calls a depth-first search helper function starting from page 0 to find all winning paths.
  dfsFindPath(path, winningPaths, 0, visited);
  //print the  winning paths
  for (size_t i = 0; i < winningPaths.size(); ++i) {
    for (size_t j = 0; j < winningPaths[i].size(); ++j) {
      std::cout << winningPaths[i][j].first;
      if (winningPaths[i][j].second != -1) {
        std::cout << "(" << winningPaths[i][j].second << ")";
      }
      if (j < winningPaths[i].size() - 1) {
        std::cout << ",";
      }
    }

    std::cout << "(win)" << std::endl;
  }
}

// This function is a depth-first search (DFS) algorithm to find all winning paths in the story.
// It is a recursive function that explores all possible paths from the current page to winning pages.
void Story::dfsFindPath(std::vector<std::pair<size_t, int> > & path,
                        std::vector<std::vector<std::pair<size_t, int> > > & winningPaths,
                        size_t currentPageNum,
                        std::set<size_t> & visited) {
  // Marks the current page as visited to avoid cycles during the DFS.
  visited.insert(currentPageNum);
  if (pages[currentPageNum].getType() == Page::W) {
    path.push_back(std::make_pair(currentPageNum, -1));

    winningPaths.push_back(path);
    path.pop_back();
  }
  else if (pages[currentPageNum].getType() != Page::L) {
    const std::vector<std::string> totalChoices = pages[currentPageNum].getChoices();
    for (size_t i = 0; i < totalChoices.size(); ++i) {
      size_t nextPage = pages[currentPageNum].getdestPageNum(i + 1);
      // if (visited.find(nextPage) == visited.end(){})
      if (std::find(visited.begin(), visited.end(), nextPage) == visited.end()) {
        // Adds the current page and choice number to the path.
        path.push_back(std::make_pair(currentPageNum, i + 1));

        // Recursively calls dfsFindPath to continue exploring the path from the next page.
        dfsFindPath(path, winningPaths, nextPage, visited);
        // Backtracks by removing the last page and choice from the path.
        path.pop_back();
        path.pop_back();
      }
    }
  }
  // Removes the current page from the visited set as the function backtracks.
  visited.erase(currentPageNum);
}

// This function starts the interactive story session. It controls the flow of the story,
// guiding the user through the pages based on their choices.
void Story::storyStart() {
  size_t currentPageNum = 0;
  while (true) {
    // Updates the story variables for the current page.
    pages[currentPageNum].updateStoryVariables(variables);
    // Retrieves conditions for choices on the current page. Conditions determine if a choice is available.
    std::map<int, std::string> currentConditions = pages[currentPageNum].getConditions();
    // for (size_t i = 0; i < pages[currentPageNum].getChoices().size(); i++) {
    //  isChoiceAvailabel(i + 1);
    // }
    std::vector<int> unvailableChoices;
    std::map<int, std::string>::const_iterator it;

    // Iterates through each condition to check if it's satisfied.
    for (it = currentConditions.begin(); it != currentConditions.end(); ++it) {
      if (!isConditionSatisfied(it->second)) {
        unvailableChoices.push_back(it->first);
      }
    }
    // Displays the current page, considering any unavailable choices.
    pages[currentPageNum].display(unvailableChoices);
    // Checks if the current page is a winning (W) or losing (L) page.
    // If so, the story session ends.
    if (pages[currentPageNum].getType() == Page::W ||
        pages[currentPageNum].getType() == Page::L) {
      break;
    }
    size_t choice;
    std::string userInput;
    bool validChoice = false;

    while (!validChoice) {
      //std::cout<<"Enter your choice: ";
      std::cin >> userInput;

      char * end;
      choice = std::strtoul(userInput.c_str(), &end, 10);

      //catch (const std::invalid_argument & e) {
      // std::cerr << "That is not a valid choice, please try again" << std::endl;
      // }
      // Checks if the entered choice is valid and available.
      // A choice is valid if it's a number within the range of available choices and not in the unavailable choices list.
      if (choice >= 1 && choice <= pages[currentPageNum].getChoices().size() &&
          *end == '\0' &&
          pages[currentPageNum].isChoiceAvailable(unvailableChoices, choice)) {
        validChoice = true;
      }
      // If the choice is not available or invalid, prompts the user to try again.
      else if (!(pages[currentPageNum].isChoiceAvailable(unvailableChoices, choice))) {
        std::cout << "That choice is not available at this time, please try again"
                  << std::endl;
      }
      else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "That is not a valid choice, please try again" << std::endl;
      }
    }
    // Updates the current page number based on the user's choice, moving the story forward.
    currentPageNum = pages[currentPageNum].getdestPageNum(choice);
  }
}
// This function validates the order in which pages are declared in the story.
void Story::validatePageDeclarationOrder(size_t pageNum) {
  // Checks if the current page number is the same as the next expected page number.
  // This ensures that pages are declared in sequential order.
  if (pageNum != nextExpectedPageNum) {
    std::ostringstream errorStr;
    errorStr << "Page declaration order error: Expected page number is "
             << nextExpectedPageNum << ". But received: " << pageNum;
    throw std::runtime_error(errorStr.str());
  }
  nextExpectedPageNum++;
}
// This function adds a choice to a specified page in the story.
void Story::addChoiceToPage(size_t pageNum,
                            size_t destPageNum,
                            const std::string & choiceText) {
  // Checks if the specified page number has already been declared.
  // This ensures that choices are only added to existing pages.
  if (declaredPages.find(pageNum) == declaredPages.end()) {
    std::ostringstream errorStr;
    errorStr << "The page corresponding to the choice is not declared: Page " << pageNum;
    throw std::runtime_error(errorStr.str());
  }
  // Adds the choice text to the specified page.
  pages[pageNum].addChoice(choiceText);
  // Associates the destination page number with the choice.
  pages[pageNum].adddestPages(destPageNum);
}

// This function checks if a string is a valid representation of a number.

size_t Story::isValidNumber(const std::string & str) {
  const char * cstr = str.c_str();
  char * endptr;
  // Parses the string into an unsigned long. If parsing fails, `endptr` will not point to the null terminator.
  size_t ans = strtoul(cstr, &endptr, 10);
  // Checks if the entire string has been successfully parsed into a number.
  if (*endptr != '\0' || endptr == NULL) {
    std::ostringstream errorStr;
    errorStr << "the pageNUM is not valid in declaration line!";
    throw std::runtime_error(errorStr.str());
  }
  return ans;
}
// This function parses a page declaration from a line of text in the story data.
// The line format generally contains the page number, page type, and the filename of the page content.
void Story::parsePageDeclaration(const std::string & line,
                                 const std::string & directory) {
  std::vector<std::string> tokens;
  std::istringstream tokenStream(line);
  std::string token;
  // Splits the line into tokens using '@' as a delimiter.
  while (std::getline(tokenStream, token, '@')) {
    tokens.push_back(token);
  }
  // Checks if the line has at least two tokens (page number and type+filename).
  if (tokens.size() >= 2) {
    // The first token is the page number as a string.
    std::string pageNumStr = tokens[0];
    // if (!isValidNumber(pageNumStr)) {
    //  std::ostringstream errorStr;
    //  errorStr << "the page number is not valid!";
    //  throw std::runtime_error(errorStr.str());
    // }
    // The second token contains the page type and filename, separated by a colon.
    std::string typeAndFileName = tokens[1];
    std::vector<std::string> typeAndFileNameTokens;
    std::istringstream typeAndFileNameStream(typeAndFileName);
    // Splits the second token into the page type and filename.
    while (std::getline(typeAndFileNameStream, token, ':')) {
      typeAndFileNameTokens.push_back(token);
    }
    // Validates that the page type and filename are correctly specified.
    if (typeAndFileNameTokens.size() == 2) {
      std::string typeChar = typeAndFileNameTokens[0];

      std::string fileName = typeAndFileNameTokens[1];
      //char* endptr;
      size_t pageNum = isValidNumber(pageNumStr);
      validatePageDeclarationOrder(pageNum);

      int typeNum = -1;
      if (typeChar == "N") {
        typeNum = 0;  // Normal page
      }
      else if (typeChar == "W") {
        typeNum = 1;  // Winning page
      }
      else if (typeChar == "L") {
        typeNum = 2;  // Losing page
      }
      else {
        // Throws an error if the page type character is invalid.
        std::ostringstream errorStr;
        errorStr << "the page type is wrong!";
        throw std::runtime_error(errorStr.str());
      }
      pages[pageNum].setType(static_cast<Page::Type>(typeNum));
      // Constructs the full path to the file containing the page content.
      std::string filenamefinal = directory + "/" + fileName;
      std::ifstream file(filenamefinal.c_str());  // Opens the file and reads its content.
      if (file.is_open()) {
        // Reads the entire file content into a string.
        std::string pageText((std::istreambuf_iterator<char>(file)),
                             (std::istreambuf_iterator<char>()));
        pages[pageNum].loadFromText(pageText);
      }
      else {
        std::ostringstream errorStr;
        errorStr << "could not open the file: " << fileName;
        throw std::runtime_error(errorStr.str());
      }
      // Marks the page number as declared.
      declaredPages.insert(pageNum);
    }
  }
}
// This function parses a line from the story data that defines a choice for a specific page.
void Story::parseChoiceLine(const std::string & line) {
  // Vector to store tokens split from the line.
  std::vector<std::string> tokens;
  std::istringstream tokenStream(line);
  std::string token;
  // Splits the line into tokens using ':' as a delimiter.
  while (std::getline(tokenStream, token, ':')) {
    tokens.push_back(token);
  }
  // Checks if the line correctly contains three tokens: page number with optional condition,
  // destination page number, and the choice text.
  if (tokens.size() == 3) {
    // The first token contains the page number and optionally a condition in square brackets.
    std::string pageNumandConditionStr = tokens[0];
    // The second token is the destination page number as a string.
    std::string destPageNumStr = tokens[1];
    // Checks for the presence of a condition in square brackets.

    size_t frontPos = pageNumandConditionStr.find('[');
    std::string pageNumStr;
    size_t pageNum = 0;
    // If a condition is present, parses both the page number and the condition.
    if (frontPos != std::string::npos) {
      size_t endPos = pageNumandConditionStr.find(']', frontPos);
      pageNumStr = pageNumandConditionStr.substr(0, frontPos);
      pageNum = isValidNumber(pageNumStr);
      // Extracts the condition substring.
      std::string condition =
          pageNumandConditionStr.substr(frontPos + 1, endPos - frontPos - 1);
      pages[pageNum].addConditions(condition, pages[pageNum].getChoices().size() + 1);
    }
    else {
      // If no condition is present, directly converts the page number string to a number.
      pageNum = isValidNumber(pageNumandConditionStr);
    }

    // if (!isValidNumber(pageNumStr)) {
    //  std::ostringstream errorStr;
    //  errorStr << "the page Num in the choice line is not valid!";
    //  throw std::runtime_error(errorStr.str());
    // }
    // size_t pageNum = isValidNumber(pageNumStr);
    //  if (!isValidNumber(destPageNumStr)) {
    //  std::ostringstream errorStr;
    //  errorStr << "the destpage num is not valid in choice line!";
    //  throw std::runtime_error(errorStr.str());
    // }

    // int pageNum = std::atoi(tokens[0].c_str());

    int destPageNum = isValidNumber(destPageNumStr);

    std::string choiceText = tokens[2];  // Extracts the choice text from the third token.

    addChoiceToPage(pageNum, destPageNum, choiceText);
  }
}
// This function loads the story data from a specified directory.
// It reads the story structure, pages, choices, and variables from a text file.
void Story::loadFromDirectory(const std::string & directory) {
  // Constructs the path to the main story file within the given directory.
  std::string storyFile = directory + "/story.txt";
  std::ifstream file(storyFile.c_str());
  if (!file.is_open()) {
    throw std::runtime_error("could not open the file: " + storyFile);
  }

  std::string line;
  // Reads the file line by line.
  while (getline(file, line)) {
    // Checks if the line contains a page declaration, which is identified by an '@' character.
    if (line.find('@') != std::string::npos) {
      parsePageDeclaration(line, directory);
    }
    // Checks if the line contains a choice definition, indicated by a ':' character.
    else if (line.find(':') != std::string::npos) {
      parseChoiceLine(line);
    }
    // Checks if the line contains a variable assignment, indicated by a '$' character.
    else if (line.find('$') != std::string::npos) {
      parseVariableAssignment(line);
    }
    // If the line is empty, skips it and continues to the next line.
    else if (line.empty()) {
      continue;
    }
    else {
      // If the line does not match any expected format, throws an error.
      std::ostringstream errorStr;
      errorStr << "the format of this line is wrong: " << line;
      throw std::runtime_error(errorStr.str());
    }
  }
}
/*
void Story::display() const {
  for (const auto & pageEntry : pages) {
    int pageNum = pageEntry.first;
    const Page & page = pageEntry.second;
    page.display(pageNum);
  }
}
*/
// This function displays the content of all pages in the story.
void Story::display() const {
  for (std::map<size_t, Page>::const_iterator it = pages.begin(); it != pages.end();
       ++it) {
    int pageNum = it->first;
    const Page & page = it->second;
    std::cout << "Page " << pageNum << "\n==========\n";
    // Calls the display function of the Page object. This function shows the content of the page.
    // An empty vector is passed as an argument, which typically represents unavailable choices.
    // Since this is a complete display for step1, no choices are marked as unavailable.
    page.display(std::vector<int>());
  }
}
