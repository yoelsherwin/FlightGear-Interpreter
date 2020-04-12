//
// Created by tal on 12.12.2019.
//

#ifndef SIMULATOR__PARSER_H_
#define SIMULATOR__PARSER_H_
using namespace std;
#include "unordered_map"
#include "Command.h"
#include "vector"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "OpenServerCommand.h"
#include "ConnectControlClientCommand.h"
#include "IfCommand.h"
#include "SleepCommand.h"
#include "ShuntingYard.h"
#include "EqualCommand.h"
#include "WhileCommand.h"
#include "FuncCommand.h"
class Parser {
  unordered_map<string, Command *> commands;
 public:
  int createFuncCommand(vector<string> array, int index);
  Parser(vector<string> array);
  unordered_map<string, Command *> getMap();
  virtual ~Parser();
 private:
  unordered_map<string, Command> map;
  void addCommandsToMap() {
    commands["var"] = new DefineVarCommand();
    commands["Print"] = new PrintCommand();
    commands["openDataServer"] = new OpenServerCommand();
    commands["connectControlClient"] = new ConnectControlClientCommand();
    commands["if"] = new IfCommand();
    commands["Sleep"] = new SleepCommand();
    commands["="] = new EqualCommand();
    commands["while"] = new WhileCommand();
  }
};

#endif //SIMULATOR__PARSER_H_
