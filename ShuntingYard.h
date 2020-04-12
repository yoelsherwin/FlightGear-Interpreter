//
// Created by yoelsh on 07/11/2019.
//

#ifndef SHUNTINGYARD_SHUNTINGYARD_H
#define SHUNTINGYARD_SHUNTINGYARD_H

#include "Expression.h"
#include "Var.h"
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

class Value : public Expression {
 private:
  const double val;

 public:
  Value(const double va);
  double calculate() override;
};

class Variable : public Expression {
 private:
  string name;
  double value;

 public:
  Variable(string name1, double value1);
  Variable &operator++();
  Variable &operator--();
  Variable &operator+=(double d);
  Variable &operator-=(double d);
  Variable &operator++(int);
  Variable &operator--(int);
  double calculate() override;

};

class BinaryOperator : public Expression {
 protected:
  Expression *left;
  Expression *right;
 public:
  BinaryOperator(Expression *left1, Expression *right1);
  virtual ~BinaryOperator() override;
};

class Plus : public BinaryOperator {
 public:
  Plus(Expression *left1, Expression *right1);
  double calculate() override;
};

class Minus : public BinaryOperator {
 public:
  Minus(Expression *left1, Expression *right1);
  double calculate() override;
};

class Mul : public BinaryOperator {
 public:
  Mul(Expression *left1, Expression *right1);
  double calculate() override;
};

class Div : public BinaryOperator {
 public:
  Div(Expression *left1, Expression *right1);
  double calculate() override;
};

class UnaryOperator : public Expression {
 protected:
  Expression *exp;
 public:
  UnaryOperator(Expression *exp1);
  virtual ~UnaryOperator() override;
};

class UPlus : public UnaryOperator {
 public:
  UPlus(Expression *exp1);
  double calculate() override;
};

class UMinus : public UnaryOperator {
 public:
  UMinus(Expression *exp1);
  double calculate() override;
};

class Interpreter {
  map<string, double> vars;
 private:
  queue<string> q;
  stack<string> operators;
 public:
  Expression *interpret(string s);
  bool inputIsValid(string s);
  void shuntingYard(string s);
  Expression *createExp();
  void generateVarAndVal(string token);
  void setVariables(string vars1);
  void setVariables(string varName, double val);
  map<string, double> GetVars();
};

#endif //EX1_EX1_H