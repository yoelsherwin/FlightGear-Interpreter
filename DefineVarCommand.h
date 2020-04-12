//
// Created by tal on 10.12.2019.
//

#ifndef SIMULATOR_COMMANDS_DEFINEVARCOMMAND_H_
#define SIMULATOR_COMMANDS_DEFINEVARCOMMAND_H_

#include "Command.h"
#include "list"
#include "Var.h"
class DefineVarCommand : public Command {
 public:
  int execute(vector<string> vector, int index) override;
};

#endif //SIMULATOR_COMMANDS_DEFINEVARCOMMAND_H_
