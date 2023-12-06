#include <cstdlib>
#include <fstream>
#include <iostream>
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

 private:
  std::map<int, Page> pages;
  std::set<int> declaredPages;
  int nextExpectedPageNum;

  std::string intToString(int num);
  void validatePageDeclarationOrder(int pageNum);
  void addChoiceToPage(int pageNum, int destPageNum, const std::string & choiceText);
  void parsePageDeclaration(const std::string & line, const std::string & directory);
  void parseChoiceLine(const std::string & line);
  bool isValidNumber(const std::string & str);
};

std::string Story::intToString(int num) {
  std::ostringstream ss;
  ss << num;
  return ss.str();
}

void Story::validatePageDeclarationOrder(int pageNum) {
  if (pageNum != nextExpectedPageNum) {
    std::ostringstream errorStr;
    errorStr << "页面声明顺序错误: 预期的页面编号是 " << nextExpectedPageNum
             << "，但得到的是 " << pageNum;
    throw std::runtime_error(errorStr.str());
  }
  nextExpectedPageNum++;
}

void Story::addChoiceToPage(int pageNum,
                            int destPageNum,
                            const std::string & choiceText) {
  if (declaredPages.find(pageNum) == declaredPages.end()) {
    std::ostringstream errorStr;
    errorStr << "选择对应的页面未声明: Page " << pageNum;
    throw std::runtime_error(errorStr.str());
  }
  pages[pageNum].addChoice(choiceText);
}
bool Story::isValidNumber(const std::string & str) {
  const char * cstr = str.c_str();
  char * endptr;
  strtol(cstr, &endptr, 10);  // 使用strtol尝试将字符串转换为整数
  // 检查转换后的endptr是否指向字符串的末尾，如果是，则整个字符串是有效数字
  return (endptr != NULL && *endptr == '\0');
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
    if (!isValidNumber(pageNumStr)) {
      std::ostringstream errorStr;
      errorStr << "the page number is not valid!";
      throw std::runtime_error(errorStr.str());
    }
    std::string typeAndFileName = tokens[1];
    std::vector<std::string> typeAndFileNameTokens;
    std::istringstream typeAndFileNameStream(typeAndFileName);
    while (std::getline(typeAndFileNameStream, token, ':')) {
      typeAndFileNameTokens.push_back(token);
    }

    if (typeAndFileNameTokens.size() == 2) {
      char typeChar = typeAndFileNameTokens[0][0];

      std::string fileName = typeAndFileNameTokens[1];

      int pageNum = std::atoi(pageNumStr.c_str());
      validatePageDeclarationOrder(pageNum);

      int typeNum = -1;
      if (typeChar == 'N') {
        typeNum = 0;
      }
      else if (typeChar == 'W') {
        typeNum = 1;
      }
      else if (typeChar == 'L') {
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
        errorStr << "无法打开文件: " << fileName;
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
    int pageNum = std::atoi(tokens[0].c_str());
    int destPageNum = std::atoi(tokens[1].c_str());
    std::string choiceText = tokens[2];

    addChoiceToPage(pageNum, destPageNum, choiceText);
  }
}

void Story::loadFromDirectory(const std::string & directory) {
  std::string storyFile = directory + "/story.txt";
  std::ifstream file(storyFile.c_str());
  if (!file.is_open()) {
    throw std::runtime_error("无法打开文件: " + storyFile);
  }

  std::string line;
  while (getline(file, line)) {
    if (line.find('@') != std::string::npos) {
      parsePageDeclaration(line, directory);
    }
    else if (line.find(':') != std::string::npos) {
      parseChoiceLine(line);
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
  for (std::map<int, Page>::const_iterator it = pages.begin(); it != pages.end(); ++it) {
    int pageNum = it->first;
    const Page & page = it->second;
    page.display(pageNum);
  }
}
