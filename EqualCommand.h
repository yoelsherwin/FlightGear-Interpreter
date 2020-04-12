//
// Created by tal on 14.12.2019.
//

#ifndef SIMULATOR__EQUALCOMMAND_H_
#define SIMULATOR__EQUALCOMMAND_H_

#include "Command.h"
//
class EqualCommand : public Command {
 public:
  int execute(vector<string> vector, int index) override;

};

#endif //SIMULATOR__EQUALCOMMAND_H_
