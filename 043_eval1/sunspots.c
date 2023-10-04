#include "sunspots.h"

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/**
 * Check if a given string represents an integer.
 * parameter: str - The input string to be checked.
 * return true if the string represents an integer, false otherwise.
 */
bool isInteger(const char * str) {
  if (str == NULL) {
    return false;  // Input is a null pointer, not an integer
  }

  int len = strlen(str);

  // Handle possible positive or negative signs
  int start = 0;
  if (str[0] == '+' || str[0] == '-') {
    start =
        1;  // If there is a positive or negative sign, start checking from the next character
  }

  // Check each character if it is a digit
  for (int i = start; i < len; i++) {
    if (!isdigit(str[i])) {
      return false;  // If there is a non-digit character, it's not an integer
    }
  }

  return true;
}

/**
 * Checks if a given string represents a valid number.
 * parameter: str The input string to be checked.
 * return true if the input string is a valid number, false otherwise.
 */
bool isNumber(const char * str) {
  int i = 0;
  bool hasDecimal = false;

  // Handle possible positive or negative signs
  if (str[i] == '+' || str[i] == '-') {
    i++;
  }

  // Check each character
  while (str[i] != '\0') {
    if (str[i] >= '0' && str[i] <= '9') {
      // Numeric character
    }
    else if (str[i] == '.' && !hasDecimal) {
      // Decimal point character, ensure only one decimal point
      hasDecimal = true;
    }
    else {
      // Non-numeric character
      return false;
    }
    i++;
  }

  // If the string ends with a decimal point, it's not a valid number
  if (str[i - 1] == '.') {
    return false;
  }

  return true;
}

/**
 * Parse a line of text into an ss_monthly_t structure.
 *
 * parameter: line The input string to be parsed.
 * return An ss_monthly_t structure containing parsed data.
 */
ss_monthly_t parseLine(char * line) {
  // WRITE ME
  ss_monthly_t ans;
  ans.year = 0;
  ans.month = 0;
  ans.num = 0;
  char * token;

  //------Extract the year number, Tokenize the input string using '-' as the delimiter.
  token = strtok(line, "-");
  //Check the error case when there is no year number
  if (token == NULL) {
    fprintf(stderr, "Wrong input! No string!\n");
    exit(EXIT_FAILURE);
  }
  //Check the error case when the year is not 4 digits
  else if (strlen(token) != 4) {
    fprintf(stderr, "Wrong input! A valid year must be 4 digits!\n");
    exit(EXIT_FAILURE);
  }
  else {
    //Check the error case when the year is not an integer
    if (isInteger(token)) {
      // Convert and assign the parsed year as an integer.
      ans.year = atoi(token);
    }
    else {
      fprintf(stderr, "Invalid input! The first part is not a number!");
      exit(EXIT_FAILURE);
    }
    //Check the error case when year number is out of the boundary [0, 9999].
    if (ans.year > 9999 || ans.year < 0) {
      fprintf(stderr, "Invalid year! Year must be in the range of [0,9999]\n");
      exit(EXIT_FAILURE);
    }
  }
  //------Extract the month numbers.Tokenize the input string using ',' as the delimiter.
  token = strtok(NULL, ",");
  //Check the error case when there is no month number
  if (token == NULL) {
    fprintf(stderr, "Wrong input!Invalid format! \n");
    exit(EXIT_FAILURE);
  }
  //Check the error case when month is not 2 digits
  else if (strlen(token) != 2) {
    fprintf(stderr, "Wrong input! A valid month must be 2 digits!");
    exit(EXIT_FAILURE);
  }
  //Check the error case when month is not an integer
  else {
    if (isInteger(token)) {
      // Convert and assign the parsed month as an integer.
      ans.month = atoi(token);
    }
    else {
      fprintf(stderr, "Invalid input! The second part is not a number!");
      exit(EXIT_FAILURE);
    }
    //Check the error case when month number is out of the boundary [0, 12].
    if (ans.month > 12 || ans.month < 0) {
      fprintf(stderr, "Wrong input! A valid month must be in the range of [0,12]");
      exit(EXIT_FAILURE);
    }
  }

  //------------------Extract the last number-----------------------
  token = strtok(NULL, "\n");
  if (token == NULL) {
    fprintf(stderr, "Wrong input! The third number does not exist!\n");
    exit(EXIT_FAILURE);
  }
  else {
    //Check the error case when the parsed number is not a number
    if (isNumber(token)) {
      // Convert and assign the parsed number as a floating-point value.
      ans.num = atof(token);
    }
    else {
      fprintf(stderr, "Invalid input! The third part is not a number!");
      exit(EXIT_FAILURE);
    }
    //Check the error case when the parsed number is not a positive number
    if (ans.num < 0) {
      fprintf(stderr, "Wrong input! The floating point number must be non-negative!\n");
      exit(EXIT_FAILURE);
    }
  }

  return ans;
}

/**
 * Apply a mean filter to smooth a series of monthly data points.
 *
 * parameter: data An array of ss_monthly_t representing the original data.
 * parameter: n The number of data points in the array.
 * parameter: mean An array to store the smoothed data after applying the filter.
 * parameter: w The width of the filter window (odd number) for calculating the mean.
 */
void meanFilter(ss_monthly_t * data, size_t n, ss_monthly_t * mean, unsigned w) {
  // WRITE ME
  // Check for invalid 'w' values
  if (w % 2 == 0 || w <= 0 || w >= n) {
    fprintf(stderr, "Invalid w!");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < n; i++) {
    // Calculate the left and right boundaries for the window
    int left = i - (w - 1) / 2;
    int right = i + (w - 1) / 2;
    // Ensure that the boundaries do not go out of bounds
    if (left < 0) {
      left = 0;
    }
    if (right > n - 1) {
      right = n - 1;
    }
    // Initialize variables to calculate the mean
    double total = 0;
    int count_num = right - left + 1;
    // Calculate the sum of 'num' values within the window
    for (int j = left; j <= right; j++) {
      total += data[j].num;
    }
    // Assign the 'year' and 'month' from the original data
    mean[i].year = data[i].year;
    mean[i].month = data[i].month;
    // Calculate and assign the mean 'num' value
    mean[i].num = total / count_num;
  }
}

/**
 * This function finds the local maximum in an array of monthly data.
 * It scans the input array and returns the timestamp of the local maximum,
 * where the local maximum is defined as the data point with the highest 'num' value.
 *
 * parameter: data An array of ss_monthly_t representing monthly data points.
 * parameter: n The number of elements in the 'data' array.
 *
 * return The timestamp (year + month/12.0) of the local maximum data point.
 *         If 'n' is 0, it exits with an error message.
 */
double findLocalMax(ss_monthly_t * data, size_t n) {
  // WRITE ME
  // Check for the error case where the input array has 0 elements.
  if (n == 0) {
    fprintf(stderr, "Invalid input!The input array has 0 elements!");
    exit(EXIT_FAILURE);
  }
  // Declare the index of the largest element, initially set to 0.
  size_t largestInd = 0;
  // Iterate through the array starting from index 1.
  for (size_t i = 1; i < n; i++) {
    //compare every element with the current largest number
    if (data[i].num > data[largestInd].num) {
      largestInd = i;
    }
  }
  //calculate the timestamp
  double timeStamp = data[largestInd].year + data[largestInd].month / 12.0;
  return timeStamp;
}

/**
 * Calculate the average time difference between timestamps.
 *
 * parameter: timeStamps An array of timestamps.
 * parameter: n The number of timestamps in the array.
 * return The average time difference.
 */
double calcSsPeriod(double * timeStamps, size_t n) {
  //WRITE ME
  //Check for error cases
  if (n < 2) {
    fprintf(stderr, "Invalid size of timeStamps! n should be at least 2!");
    exit(EXIT_FAILURE);
  }
  // Create an array to store the time differences between timestamps
  double timeStamp_diff[n - 1];
  double diff_sum = 0;
  // Calculate the absolute differences between adjacent timestamps
  for (size_t i = 0; i < n - 1; i++) {
    timeStamp_diff[i] = fabs(timeStamps[i + 1] - timeStamps[i]);
    //calculate the sum of the elements in timeStamp_diff
    diff_sum += timeStamp_diff[i];
  }
  // Calculate the average difference between timestamps// Calculate the average difference between timestamps
  double averageDiff = diff_sum / (n - 1);

  return averageDiff;
}
