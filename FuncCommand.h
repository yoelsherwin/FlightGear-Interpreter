//
// Created by tal on 23/12/2019.
//

#ifndef SIMULATOR__FUNCCOMMAND_H_
#define SIMULATOR__FUNCCOMMAND_H_

#include "Command.h"
class FuncCommand : public Command {
  vector<string> funcVec;
  string var;
 public:
  FuncCommand(vector<string> vec, string var1);
  int execute(vector<string> vector, int index) override;

};

#endif //SIMULATOR__FUNCCOMMAND_H_
