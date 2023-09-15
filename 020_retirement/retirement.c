#include <stdio.h>
#include <stdlib.h>
// so we are explore how to write this retirement saving caculator
//the first thing is to construct two structures
struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;
double balance_calculation(double recentBalance, retire_info status);
double balance_calculation(double recentBalance, retire_info status) {
  double newBalance = recentBalance * (1 + status.rate_of_return) + status.contribution;
  return newBalance;
}
//next step is to write a function to compute the total balance
void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  //the function performs two tasks.
  //now it will do the first one: compute the retirement account balance each month while working.
  //let me think about it
  //现在思路理清了，就是这个函数主要是根据输入的开始年龄（最开始的输入是全月份数的），和最开始的金额，以及两个structure中规定的
  //工作月数，每个月赚的钱，利息和退休月数，每个月花的钱
  //然后我们要从initial开始首先计算在working status‘s balance for each month. how to do it? use a for loop when the month increases
  //calculate the balance and then print it with the age (based on year and month), then change the year and month
  //then also the retire status
  // the first is declare the local variables:
  int age_year = startAge / 12;
  int age_month = startAge % 12;
  double now_balance = initial;
  for (int i = 0; i < working.months; i++) {
    //then calculate the banlance for each month
    printf("Age %3d month %2d you have $%.2lf\n", age_year, age_month, now_balance);
    now_balance = balance_calculation(now_balance, working);
    if (age_month == 11) {
      age_month = 0;
      age_year++;
    }
    else {
      age_month++;
    }
  }
  //retire status
  for (int j = 0; j < retired.months; j++) {
    printf("Age %3d month %2d you have $%.2lf\n", age_year, age_month, now_balance);
    now_balance = balance_calculation(now_balance, retired);
    if (age_month == 11) {
      age_month = 0;
      age_year++;
    }
    else {
      age_month++;
    }
  }
  return;
}

//main function for check some cases for this code

int main() {
  int startAge = 327;
  double initial = 21345;
  retire_info working;
  retire_info retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(startAge, initial, working, retired);
  return 0;
}
