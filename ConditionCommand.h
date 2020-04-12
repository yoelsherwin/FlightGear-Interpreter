//
// Created by tal on 12.12.2019.
//

#ifndef SIMULATOR__CONDITIONCOMMAND_H_
#define SIMULATOR__CONDITIONCOMMAND_H_

#include "Command.h"
class ConditionCommand : public Command {
 public:
  bool flag;
  bool IsConditionIsTrue(std::string stringOfCondition);

};

#endif //SIMULATOR__CONDITIONCOMMAND_H_
