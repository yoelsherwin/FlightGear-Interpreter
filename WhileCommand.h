//
// Created by tal on 12.12.2019.
//

#ifndef SIMULATOR__WHILECOMMAND_H_
#define SIMULATOR__WHILECOMMAND_H_
#include "Command.h"
#include "ConditionCommand.h"
#include "list"
class WhileCommand : public ConditionCommand {
 public:
  int execute(vector<string> vector, int index) override;
};

#endif //SIMULATOR__WHILECOMMAND_H_
