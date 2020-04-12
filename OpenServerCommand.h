//
// Created by yoelsh on 10/12/2019.
//

#ifndef SIMULATOR_COMMANDS_OPENSERVERCOMMAND_H_
#define SIMULATOR_COMMANDS_OPENSERVERCOMMAND_H_

#include "Command.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include "Variables.h"
#include <vector>

class OpenServerCommand : public Command {
 public:
  int client_socket;
  int execute(vector<string> vector, int index) override;
};

#endif //SIMULATOR_COMMANDS_OPENSERVERCOMMAND_H_
