#ifndef _EXPR_H_
#define _EXPR_H_
//#include <cstdlib>
//#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual ~Expression(){};
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression(long num) : num(num) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << num;
    return ans.str();
  }
  //  return std::to_string(num); }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return ans.str();
  }
  ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

#endif
