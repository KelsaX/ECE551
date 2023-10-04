#include "sunspots.h"

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
bool isNumber(const char * str) {
  int i = 0;
  bool hasDecimal = false;

  // 处理可能的正负号
  if (str[i] == '+' || str[i] == '-') {
    i++;
  }

  // 检查每个字符
  while (str[i] != '\0') {
    if (str[i] >= '0' && str[i] <= '9') {
      // 数字字符
    }
    else if (str[i] == '.' && !hasDecimal) {
      // 小数点字符，确保只有一个小数点
      hasDecimal = true;
    }
    else {
      // 非数字字符
      return false;
    }
    i++;
  }

  // 如果字符串以小数点结尾也不是数字
  if (str[i - 1] == '.') {
    return false;
  }

  return true;
}
ss_monthly_t parseLine(char * line) {
  // WRITE ME
  ss_monthly_t ans;
  ans.year = 0;
  ans.month = 0;
  ans.num = 0;
  char * token;

  //Extract the year numbers
  token = strtok(line, "-");
  if (token == NULL) {
    fprintf(stderr, "Wrong input! No string!\n");
    exit(EXIT_FAILURE);
  }
  else if (strlen(token) != 4) {
    fprintf(stderr, "Wrong input! A valid year must be 4 digits!\n");
    exit(EXIT_FAILURE);
  }
  else {
    if (isNumber(token)) {
      ans.year = atoi(token);
    }
    else {
      fprintf(stderr, "Invalid input! The first part is not a number!");
      exit(EXIT_FAILURE);
    }
    if (ans.year > 9999 || ans.year < 0) {
      fprintf(stderr, "Invalid year! Year must be in the range of [0,9999]\n");
      exit(EXIT_FAILURE);
    }
  }
  //Extract the month numbers
  token = strtok(NULL, ",");
  if (token == NULL) {
    fprintf(stderr, "Wrong input!Invalid format! \n");
    exit(EXIT_FAILURE);
  }
  else if (strlen(token) != 2) {
    fprintf(stderr, "Wrong input! A valid month must be 2 digits!");
    exit(EXIT_FAILURE);
  }
  else {
    if (isNumber(token)) {
      ans.month = atoi(token);
    }
    else {
      fprintf(stderr, "Invalid input! The second part is not a number!");
      exit(EXIT_FAILURE);
    }
    if (ans.month > 12 || ans.month < 0) {
      fprintf(stderr, "Wrong input! A valid month must be in the range of [0,12]");
      exit(EXIT_FAILURE);
    }
  }
  //Extract the last number
  token = strtok(NULL, "\n");
  if (token == NULL) {
    fprintf(stderr, "Wrong input! The third number does not exist!\n");
    exit(EXIT_FAILURE);
  }
  else {
    if (isNumber(token)) {
      ans.num = atof(token);
    }
    else {
      fprintf(stderr, "Invalid input! The third part is not a number!");
      exit(EXIT_FAILURE);
    }

    if (ans.num < 0) {
      fprintf(stderr, "Wrong input! The floating point number must be non-negative!\n");
      exit(EXIT_FAILURE);
    }
  }

  return ans;
}

void meanFilter(ss_monthly_t * data, size_t n, ss_monthly_t * mean, unsigned w) {
  // WRITE ME
  if (w % 2 == 0 || w <= 0 || w >= n) {
    fprintf(stderr, "Invalid w!");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < n; i++) {
    int left = i - (w - 1) / 2;
    int right = i + (w - 1) / 2;
    if (left < 0) {
      left = 0;
    }
    if (right > n - 1) {
      right = n - 1;
    }
    double total = 0;
    int count_num = right - left + 1;
    for (int j = left; j <= right; j++) {
      total += data[j].num;
    }
    mean[i].year = data[i].year;
    mean[i].month = data[i].month;
    mean[i].num = total / count_num;
  }
}

double findLocalMax(ss_monthly_t * data, size_t n) {
  // WRITE ME
  //error case
  if (n == 0) {
    fprintf(stderr, "Invalid input!The input array has 0 elements!");
    exit(EXIT_FAILURE);
  }
  //declare the largest index
  size_t largestInd = 0;
  //count i from 1 to n
  for (size_t i = 1; i < n; i++) {
    //compare every element with the current largest number
    if (data[i].num > data[largestInd].num) {
      largestInd = i;
    }
  }
  //calculate the time stamp
  double timeStamp = data[largestInd].year + data[largestInd].month / 12.0;
  return timeStamp;
}
double calcSsPeriod(double * timeStamps, size_t n) {
  //WRITE ME
  //error case
  if (n < 2) {
    fprintf(stderr, "Invalid size of timeStamps! n should be at least 2!");
    exit(EXIT_FAILURE);
  }
  double timeStamp_diff[n - 1];
  double diff_sum = 0;
  for (size_t i = 0; i < n - 1; i++) {
    timeStamp_diff[i] = fabs(timeStamps[i + 1] - timeStamps[i]);
    //calculate the sum of the elements in timeStamp_diff
    diff_sum += timeStamp_diff[i];
  }

  double averageDiff = diff_sum / (n - 1);

  return averageDiff;
}
