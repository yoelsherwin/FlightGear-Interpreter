//
// Created by tal on 12.12.2019.
//

#include "Var.h"
#include "Variables.h"
Var::Var(double value1, const string &sim1, bool is_input) {
  value = value1;
  simPath = sim1;
  bindedFromLeftToRight = is_input;
  Variables::getInstance();
}
double Var::GetValue() const {
  return value;
}

const string &Var::GetSim() const {
  return simPath;

}

void Var::setValue(double value1) {
  this->value = value1;
}

void Var::setSim(const string &sim) {
  Var::simPath = sim;
}

void Var::setBindedFromLeftToRight(bool bindedFromLeftToRight1) {
  Var::bindedFromLeftToRight = bindedFromLeftToRight1;
}

bool Var::isBindedFromRightToLeft() const {
  return bindedFromLeftToRight;
}
