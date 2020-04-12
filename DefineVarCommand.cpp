//
// Created by tal on 10.12.2019.
//

#include <cstring>
#include "DefineVarCommand.h"
int DefineVarCommand::execute(vector<string> vector, int index) {
  string name = vector[index + 1];
  bool bindedToRight = false;
  if (vector[index + 1].find("=") != string::npos) {
    return 1;
  }
  if (vector[index + 2] == "->")
    bindedToRight = true;
  string simLocation = vector[index + 4];
  //remove the / at the start and the end.
  simLocation = simLocation.substr(1, simLocation.size() - 2);
  // iterate over map of vars of sim to find the correct var.
  // after var is found, insert var with the var name to program map
  for (std::pair<std::string, Var *> element : Variables::getInstance()->getSimMap()) {
    if (strcmp(element.second->GetSim().c_str(), simLocation.c_str()) == 0) {
      Variables::getInstance()->programMap[name] = element.second;
      Variables::getInstance()->fromPathToVar[simLocation] = name;
      Variables::getInstance()->programMap[name]->setBindedFromLeftToRight(bindedToRight);
      Variables::getInstance()->i1->setVariables(name, 0);
    }
  }
  return 5;
}