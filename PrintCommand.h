//
// Created by tal on 12.12.2019.
//

#ifndef SIMULATOR__PRINTCOMMAND_H_
#define SIMULATOR__PRINTCOMMAND_H_

#include "Command.h"
#include "DefineVarCommand.h"
class PrintCommand : public Command {
 public:
  DefineVarCommand *vars;
  int execute(vector<string> vector, int index) override;

};

#endif //SIMULATOR__PRINTCOMMAND_H_
