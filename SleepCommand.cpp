//
// Created by tal on 12.12.2019.
//
//

#include "SleepCommand.h"
int SleepCommand::execute(vector<string> vector, int index) {
  std::this_thread::sleep_for(std::chrono::milliseconds(stoi(vector[index + 1])));
  return 2;
}
