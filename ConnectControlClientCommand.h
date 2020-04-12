//
// Created by tal on 12.12.2019.
//

#ifndef SIMULATOR__CONNECTCONTROLCLIENTCOMMAND_H_
#define SIMULATOR__CONNECTCONTROLCLIENTCOMMAND_H_
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "thread"
#include "Command.h"
class ConnectControlClientCommand : public Command {
 public:
  int execute(vector<string> vector, int index) override;
};

#endif //SIMULATOR__CONNECTCONTROLCLIENTCOMMAND_H_
