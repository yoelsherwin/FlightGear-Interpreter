//
// Created by tal on 12.12.2019.
//

#include <algorithm>
#include "Lexer.h"
Lexer::Lexer(string fileName) {
  unsigned i = 0;
  string line, temp = "";
  vector<string> vec;
  fstream file;

  // open file
  file.open(fileName, ios::in);
  if (!file) {
    cout << "bad file" << endl;
  }

  //cross on the file line-line
  while (!file.eof()) {
    getline(file, line);

    // check for specific cases
    string checkVar = line.substr(0, 3);
    string checkWhile = line.substr(0, 5);
    string checkIf = line.substr(0, 2);
    auto findEqual = line.find_first_of("=");
    auto findQuote = line.find_first_of('"');

    // if it's an assignment of existing var.
    // we want to ignore the = sign if its a while/if/var command or a string
    if (!(checkVar == "var" || checkVar == "Var") &&    //var
        !(checkWhile == "while" || checkWhile == "While") &&    //while
        !(checkIf == "if" || checkIf == "If") &&    //if
        (findEqual != string::npos && findQuote == string::npos)) {   //string. plus check for equal sign
      // erase spaces
      line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
      line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
      // insert whole line
      vec.insert(vec.end(), line);
      // skip to next line
      continue;
    }

    //insert a string and split the strings by ' ', '(', ')', ','
    while (i < line.size()) {
      while (i < line.size() && line[i] != '(' && line[i] != ')' && line[i] != ',') {
        // if condition - insert all line. will be splitted later
        if(checkWhile == "while" || checkWhile == "While" || checkIf == "if" || checkIf == "If") {
          temp = line;
          i = line.size();
          break;
        }

        // every other case
        temp += line[i];
        i++;
        // if its a quote
        if(line[i-1] == '"') {
          // insert until quote finished
          while(line[i] != '"') {
            temp += line[i];
            i++;
          }
          // insert last "
          temp+= line[i];
          i++;
        }
      }

      //erase tabs
      temp.erase(std::remove(temp.begin(), temp.end(), '\t'), temp.end());
      temp.erase(std::remove(temp.begin(), temp.end(), '\r'), temp.end());
      // what kind of line is it?
      auto check = temp.find("while");
      auto check1 = temp.find("var");
      auto check3 = temp.find("if");
      // if it is a while command - split correctly
      if (check != string::npos || check3 != string::npos) {
        string temp1;
        // insert while
        if (check != string::npos) {
          temp1 = temp.substr(check, 5);
        } else {    // insert if
          temp1 = temp.substr(check3, 2);
        }
        vec.insert(vec.end(), temp1);
        // insert condition
        auto check2 = temp.size() - temp1.size();
        if (check != string::npos) {
          temp1 = temp.substr(check + 6, check2);
        } else {    // insert if
          temp1 = temp.substr(check + 3, check2);
        }
        //temp1 = temp1.substr(0, temp1.size() - 1);
        temp1.erase(std::remove_if(temp1.begin(), temp1.end(), ::isspace), temp1.end());
        temp1.erase(std::remove(temp1.begin(), temp1.end(), '('), temp1.end());
        temp1.erase(std::remove(temp1.begin(), temp1.end(), ')'), temp1.end());
        temp1.erase(std::remove(temp1.begin(), temp1.end(), '{'), temp1.end());
        vec.insert(vec.end(), temp1);
        // insert the {
        vec.insert(vec.end(), "{");
      }
        // if it is a var command - split correctly
      else if (check1 != string::npos) {
        // insert "val"
        string temp1 = temp.substr(check1, 3);
        vec.insert(vec.end(), temp1);
        if (temp.length() > 3 && temp.substr(4, temp.length() - 4).find_first_of("->") == string::npos &&
            temp.substr(4, temp.length() - 4).find_first_of("<-") == string::npos) {
          temp.erase(std::remove(temp.begin(), temp.end(), '\r'), temp.end());
          vec.insert(vec.end(), temp.substr(4, temp.length() - 4));
        }
          // if its a new var being binded
        else {
          // insert name of val
          auto check2 = temp.find("<-");
          if (check2 == string::npos) {
            check2 = temp.find("->");
          }
          if (check2 != string::npos) {
            temp1 = temp.substr(check1 + 4, check2 - (check1 + 4));
            temp1.erase(std::remove_if(temp1.begin(), temp1.end(), ::isspace), temp1.end());
            vec.insert(vec.end(), temp1);
            // insert arrow
            temp1 = temp.substr(check2, 2);
            vec.insert(vec.end(), temp1);
            // insert sim
            check2 = temp.find("sim");
            temp1 = temp.substr(check2, 3);
            vec.insert(vec.end(), temp1);
          }
        }
      } else {    //every other case
        if (temp.find(34) == string::npos)    // if string is without quote ,delete spaces
          temp.erase(std::remove(temp.begin(), temp.end(), 32), temp.end());
        if(temp != "\r" && temp != "\t" && temp != "\r" && temp != " "&& temp != "")
          vec.insert(vec.end(), temp);
      }
      //initialize the parameters.
      temp = "";
      i++;
    }
    //initialize i for the next line.(if there is more line)
    i = 0;
  }

  // print for checks

  /*
  for (i = 0; i < vec.size(); i++) {
    cout << vec[i] << endl;
  }
   */


  this->array = vec;
}
