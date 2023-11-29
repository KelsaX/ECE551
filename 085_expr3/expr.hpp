#ifndef _EXPR_HPP_
#define _EXPR_HPP_
#include <sstream>
#include <string>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
  virtual long evaluate() const = 0;
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
  virtual ~NumExpression() {}
  virtual long evaluate() const { return num; }
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
  virtual long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
};

class MinusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    return ans.str();
  }
  ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
  virtual long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
};

class TimesExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    return ans.str();
  }
  ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
  virtual long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
};

class DivExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    return ans.str();
  }
  ~DivExpression() {
    delete lhs;
    delete rhs;
  }
  virtual long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
};
#endif
