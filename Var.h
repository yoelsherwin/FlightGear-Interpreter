//
// Created by tal on 12.12.2019.
//

#ifndef SIMULATOR__VAR_H_
#define SIMULATOR__VAR_H_
#include <string>
using namespace std;
class Var {
  double value;
  string simPath;
  bool bindedFromLeftToRight;
 public:
  Var(double value, const string &sim, bool is_input);
  const string &GetSim() const;
  double GetValue() const;

  bool isBindedFromRightToLeft() const;

  void setValue(double value);

  void setSim(const string &sim);

  void setBindedFromLeftToRight(bool bindedFromRightToLeft1);

};

#endif //SIMULATOR__VAR_H_
