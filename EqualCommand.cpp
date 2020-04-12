//
// Created by tal on 14.12.2019.
//

#include <algorithm>
#include "EqualCommand.h"
int EqualCommand::execute(vector<string> vector, int index) {
  //insert to the map of the interpreter.
  vector[index].erase(std::remove_if(vector[index].begin(), vector[index].end(), ::isspace), vector[index].end());
  // do shunting yard on right. concatenate to left and then continue
  string var;
  double val;
  string delimiter = "=";
  size_t pos = 0;

  // check if there's a "=" in the string
  if ((pos = vector[index].find(delimiter)) == string::npos) {
    throw ("variable string not valid");
  }
  // splitting the string by the delimiter
  var = vector[index].substr(0, pos);
  val = Variables::getInstance()->doShuntingYard(vector[index].erase(0, pos + delimiter.length()));
  vector[index] = "";
  vector[index] = var + "=" + to_string(val);
  //and vector[index] to var map
  Variables::getInstance()->addVarToMap(vector[index]);
  return 1;
}