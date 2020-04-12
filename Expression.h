//
// Created by yoelsh on 12/12/2019.
//

#ifndef SIMULATOR__EXPRESSION_H_
#define SIMULATOR__EXPRESSION_H_

using namespace std;
/**
 * Expression Interface
 */
class Expression {

 public:
  virtual double calculate() = 0;
  virtual ~Expression() {}
};

#endif //SIMULATOR__EXPRESSION_H_
