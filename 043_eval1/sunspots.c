#include "sunspots.h"

#include <stdlib.h>
#include <string.h>
ss_monthly_t parseLine(char * line) {
  // WRITE ME
  ss_monthly_t ans;
  ans.year = 0;
  ans.month = 0;
  ans.num = 0;
  char * token;

  //Extract the year numbers
  token = strtok(line, "-,");
  if (token == NULL) {
    printf("Wrong input! No string!");
    exit(EXIT_FAILURE);
  }
  else if (strlen(token) != 4) {
    printf("Wrong input! A valid year must be 4 digits!");
    exit(EXIT_FAILURE);
  }
  else {
    ans.year = atoi(token);
    if (ans.year > 9999 || ans.year < 0) {
      printf("Invalid year! Year must be in the range of [0,9999]");
      exit(EXIT_FAILURE);
    }
  }
  //Extract the month numbers
  token = strtok(NULL, "-,");
  if (token == NULL) {
    printf("Wrong input!Invalid format！Maybe no ,");
    exit(EXIT_FAILURE);
  }
  else if (strlen(token) != 2) {
    printf("Wrong input! A valid month must be 2 digits!");
    exit(EXIT_FAILURE);
  }
  else {
    ans.month = atoi(token);
    if (ans.month > 12 || ans.month < 0) {
      printf("Wrong input! A valid month must be in the range of [0,12]");
      exit(EXIT_FAILURE);
    }
  }
  //Extract the last number
  token = strtok(NULL, "-,");
  if (token == NULL) {
    printf("Wrong input! The third number does not exist!");
    exit(EXIT_FAILURE);
  }
  else {
    ans.num = atof(token);
    if (ans.num < 0) {
      printf("Wrong input! The floating point number must be non-negative!");
      exit(EXIT_FAILURE);
    }
  }

  return ans;
}

void meanFilter(ss_monthly_t * data, size_t n, ss_monthly_t * mean, unsigned w) {
  // WRITE ME
}

double findLocalMax(ss_monthly_t * data, size_t n) {
  // WRITE ME
  return 0;
}

double calcSsPeriod(double * timeStamps, size_t n) {
  //WRITE ME
  return 0;
}
