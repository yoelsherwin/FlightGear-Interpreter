//
// Created by tal on 12.12.2019.
//

#include <mutex>
#include "Parser.h"
#include "FuncCommand.h"

Parser::Parser(vector<string> array) {
  // parse vector and execute through map
  addCommandsToMap();
  unsigned index = 0;
  Command *c;
  // executing every command
  while (index < array.size()) {
    if (array[index].find("=") != string::npos) {
      c = commands["="];
      index += c->execute(array, index);
    } else {
      if (commands.count(array[index]) > 0) {
        c = commands[array[index]];
        index += c->execute(array, index);
      } else {
        index += createFuncCommand(array, index);
      }
    }
    //cout << "after index" << index << endl;
  }
}
unordered_map<string, Command *> Parser::getMap() {
  return this->commands;
}
Parser::~Parser() {
  for (pair<string, Command *> element: commands) {
    delete element.second;
  }

}
int Parser::createFuncCommand(vector<string> vector1, int index) {
  vector<string> funcVec;
  int countParent = 1;
  int countIndex = index + 4;
  while (countParent) {
    funcVec.push_back(vector1[countIndex]);
    countIndex++;
    if (vector1[countIndex] == "{")
      countParent++;
    if (vector1[countIndex] == "}")
      countParent--;
  }
  commands[vector1[index]] = new FuncCommand(funcVec, vector1[index + 2]);
  return countIndex - index + 1;
}

