//
// Created by tal on 12.12.2019.
//
#include "Parser.h"
#include "IfCommand.h"
int IfCommand::execute(vector<string> vector1, int index) {
  vector<string> tempStringToParsInWhile;
  int saveTheNumberOfTheLastIndexInWhile = index + 3;
  while (vector1[saveTheNumberOfTheLastIndexInWhile] != "}") {
    tempStringToParsInWhile.push_back(vector1[saveTheNumberOfTheLastIndexInWhile]);
    saveTheNumberOfTheLastIndexInWhile++;
  }
  flag = IsConditionIsTrue(vector1[index + 1]);
  if (flag) {
    Parser *par = new Parser(tempStringToParsInWhile);
    flag = IsConditionIsTrue(vector1[index + 1]);
    delete par;
  }
  //check how much indexes are in the while!
  return saveTheNumberOfTheLastIndexInWhile - index + 1;
}
