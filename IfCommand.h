//
// Created by tal on 12.12.2019.
//

#ifndef SIMULATOR__IFCOMMAND_H_
#define SIMULATOR__IFCOMMAND_H_

#include "ConditionCommand.h"
class IfCommand : public ConditionCommand {
 public:
  int execute(vector<string> vector, int index) override;
  Command command;

};

#endif //SIMULATOR__IFCOMMAND_H_
