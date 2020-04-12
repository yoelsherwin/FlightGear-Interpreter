//
// Created by tal on 12.12.2019.
//

#ifndef SIMULATOR__LEXER_H_
#define SIMULATOR__LEXER_H_
using namespace std;
#include "vector"
#include "string"
#include "iostream"
#include "fstream"

class Lexer {
 public:
  Lexer(string fileName);
  vector<string> array;
};

#endif //SIMULATOR__LEXER_H_
