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
class Story {
 public:
  Story() : nextExpectedPageNum(0) {}

  void loadFromDirectory(const std::string & directory);
  void display() const;
  void storyStart();
  void findWinningPaths();

 private:
  std::map<size_t, Page> pages;
  std::set<size_t> declaredPages;
  size_t nextExpectedPageNum;
  std::map<std::string, int> variables;
  // std::string intToString(int num);
  void validatePageDeclarationOrder(size_t pageNum);
  void addChoiceToPage(size_t pageNum,
                       size_t destPageNum,
                       const std::string & choiceText);
  void parsePageDeclaration(const std::string & line, const std::string & directory);
  void parseChoiceLine(const std::string & line);
  size_t isValidNumber(const std::string & str);
  // void findWinningPaths();
  void dfsFindPath(std::vector<std::pair<size_t, int> > & path,
                   std::vector<std::vector<std::pair<size_t, int> > > & winningPaths,
                   size_t currentPageNum,
                   std::set<size_t> & visited);
  void parseVariableAssignment(const std::string & line);
  // bool isChoiceAvailable(int choice);
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
bool Story::isConditionSatisfied(const std::string & condition) {
  size_t equalPos = condition.find('=');
  if (equalPos == std::string::npos) {
    throw std::runtime_error("Condition format error: " + condition);
  }
  std::string variableName = condition.substr(0, equalPos);
  int expectedValue = isValidNumber(condition.substr(equalPos + 1));
  std::map<std::string, int>::iterator it = variables.find(variableName);
  if (it != variables.end()) {
    return it->second == expectedValue;
  }
  return expectedValue == 0;
}

void Story::parseVariableAssignment(const std::string & line) {
  std::istringstream lineStream(line);
  std::string pageToSet;
  std::getline(lineStream, pageToSet, '$');
  std::string variableAssignment;
  size_t pageNum = isValidNumber(pageToSet);
  if (std::getline(lineStream, variableAssignment)) {
    size_t equalPos = variableAssignment.find('=');
    if (equalPos == std::string::npos) {
      std::ostringstream errorStr;
      errorStr << "the variable assignment is not valid";
      throw std::runtime_error(errorStr.str());
    }
    std::string variableName = variableAssignment.substr(0, equalPos);
    std::string valueStr = variableAssignment.substr(equalPos + 1);
    int value = isValidNumber(valueStr);
    // variable[variableName] = value;
    pages[pageNum].addVariables(variableName, value);
  }
  else {
    std::ostringstream errorStr;
    errorStr << "the format of the variable assignment line is not valid";
    throw std::runtime_error(errorStr.str());
  }
}
void Story::findWinningPaths() {
  std::vector<std::pair<size_t, int> > path;
  std::vector<std::vector<std::pair<size_t, int> > > winningPaths;
  std::set<size_t> visited;
  dfsFindPath(path, winningPaths, 0, visited);
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
void Story::dfsFindPath(std::vector<std::pair<size_t, int> > & path,
                        std::vector<std::vector<std::pair<size_t, int> > > & winningPaths,
                        size_t currentPageNum,
                        std::set<size_t> & visited) {
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
        path.push_back(std::make_pair(currentPageNum, i + 1));
        dfsFindPath(path, winningPaths, nextPage, visited);
        path.pop_back();
      }
    }
  }
  visited.erase(currentPageNum);
}
void Story::storyStart() {
  size_t currentPageNum = 0;
  while (true) {
    pages[currentPageNum].updateStoryVariables(variables);
    std::map<int, std::string> currentConditions = pages[currentPageNum].getConditions();
    // for (size_t i = 0; i < pages[currentPageNum].getChoices().size(); i++) {
    //  isChoiceAvailabel(i + 1);
    // }
    std::vector<int> unvailableChoices;
    std::map<int, std::string>::const_iterator it;
    for (it = currentConditions.begin(); it != currentConditions.end(); ++it) {
      if (!isConditionSatisfied(it->second)) {
        unvailableChoices.push_back(it->first);
      }
    }

    pages[currentPageNum].display(unvailableChoices);
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

      if (choice >= 1 && choice <= pages[currentPageNum].getChoices().size() &&
          *end == '\0' &&
          pages[currentPageNum].isChoiceAvailable(unvailableChoices, choice)) {
        validChoice = true;
      }
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

    currentPageNum = pages[currentPageNum].getdestPageNum(choice);
  }
}
void Story::validatePageDeclarationOrder(size_t pageNum) {
  if (pageNum != nextExpectedPageNum) {
    std::ostringstream errorStr;
    errorStr << "Page declaration order error: Expected page number is "
             << nextExpectedPageNum << ". But received: " << pageNum;
    throw std::runtime_error(errorStr.str());
  }
  nextExpectedPageNum++;
}

void Story::addChoiceToPage(size_t pageNum,
                            size_t destPageNum,
                            const std::string & choiceText) {
  if (declaredPages.find(pageNum) == declaredPages.end()) {
    std::ostringstream errorStr;
    errorStr << "The page corresponding to the choice is not declared: Page " << pageNum;
    throw std::runtime_error(errorStr.str());
  }
  pages[pageNum].addChoice(choiceText);
  pages[pageNum].adddestPages(destPageNum);
}
size_t Story::isValidNumber(const std::string & str) {
  const char * cstr = str.c_str();
  char * endptr;
  size_t ans = strtoul(cstr, &endptr, 10);
  if (*endptr != '\0' || endptr == NULL) {
    std::ostringstream errorStr;
    errorStr << "the pageNUM is not valid in declaration line!";
    throw std::runtime_error(errorStr.str());
  }
  return ans;
}
void Story::parsePageDeclaration(const std::string & line,
                                 const std::string & directory) {
  std::vector<std::string> tokens;
  std::istringstream tokenStream(line);
  std::string token;

  while (std::getline(tokenStream, token, '@')) {
    tokens.push_back(token);
  }

  if (tokens.size() >= 2) {
    std::string pageNumStr = tokens[0];
    // if (!isValidNumber(pageNumStr)) {
    //  std::ostringstream errorStr;
    //  errorStr << "the page number is not valid!";
    //  throw std::runtime_error(errorStr.str());
    // }
    std::string typeAndFileName = tokens[1];
    std::vector<std::string> typeAndFileNameTokens;
    std::istringstream typeAndFileNameStream(typeAndFileName);
    while (std::getline(typeAndFileNameStream, token, ':')) {
      typeAndFileNameTokens.push_back(token);
    }

    if (typeAndFileNameTokens.size() == 2) {
      std::string typeChar = typeAndFileNameTokens[0];

      std::string fileName = typeAndFileNameTokens[1];
      //char* endptr;
      size_t pageNum = isValidNumber(pageNumStr);
      validatePageDeclarationOrder(pageNum);

      int typeNum = -1;
      if (typeChar == "N") {
        typeNum = 0;
      }
      else if (typeChar == "W") {
        typeNum = 1;
      }
      else if (typeChar == "L") {
        typeNum = 2;
      }
      else {
        std::ostringstream errorStr;
        errorStr << "the page type is wrong!";
        throw std::runtime_error(errorStr.str());
      }
      pages[pageNum].setType(static_cast<Page::Type>(typeNum));

      std::string filenamefinal = directory + "/" + fileName;
      std::ifstream file(filenamefinal.c_str());
      if (file.is_open()) {
        std::string pageText((std::istreambuf_iterator<char>(file)),
                             (std::istreambuf_iterator<char>()));
        pages[pageNum].loadFromText(pageText);
      }
      else {
        std::ostringstream errorStr;
        errorStr << "could not open the file: " << fileName;
        throw std::runtime_error(errorStr.str());
      }

      declaredPages.insert(pageNum);
    }
  }
}

void Story::parseChoiceLine(const std::string & line) {
  std::vector<std::string> tokens;
  std::istringstream tokenStream(line);
  std::string token;
  while (std::getline(tokenStream, token, ':')) {
    tokens.push_back(token);
  }

  if (tokens.size() == 3) {
    std::string pageNumandConditionStr = tokens[0];
    std::string destPageNumStr = tokens[1];

    size_t frontPos = pageNumandConditionStr.find('[');
    std::string pageNumStr;
    size_t pageNum = 0;
    if (frontPos != std::string::npos) {
      size_t endPos = pageNumandConditionStr.find(']', frontPos);
      pageNumStr = pageNumandConditionStr.substr(0, frontPos);
      pageNum = isValidNumber(pageNumStr);
      std::string condition =
          pageNumandConditionStr.substr(frontPos + 1, endPos - frontPos - 1);
      pages[pageNum].addConditions(condition, pages[pageNum].getChoices().size() + 1);
    }
    else {
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

    std::string choiceText = tokens[2];

    addChoiceToPage(pageNum, destPageNum, choiceText);
  }
}

void Story::loadFromDirectory(const std::string & directory) {
  std::string storyFile = directory + "/story.txt";
  std::ifstream file(storyFile.c_str());
  if (!file.is_open()) {
    throw std::runtime_error("could not open the file: " + storyFile);
  }

  std::string line;
  while (getline(file, line)) {
    if (line.find('@') != std::string::npos) {
      parsePageDeclaration(line, directory);
    }
    else if (line.find(':') != std::string::npos) {
      parseChoiceLine(line);
    }
    else if (line.find('$') != std::string::npos) {
      parseVariableAssignment(line);
    }
    else if (line.empty()) {
      continue;
    }
    else {
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

void Story::display() const {
  for (std::map<size_t, Page>::const_iterator it = pages.begin(); it != pages.end();
       ++it) {
    int pageNum = it->first;
    const Page & page = it->second;
    std::cout << "Page " << pageNum << "\n==========\n";

    page.display(std::vector<int>());
  }
}
