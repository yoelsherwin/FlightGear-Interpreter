//
// Created by tal on 19/12/2019.
//

#include "ConditionCommand.h"

bool ConditionCommand::IsConditionIsTrue(std::string stringOfCondition) {
  string DelimitierOfEqual = "==";
  string DelimitierOfBigOrEqual = ">=";
  string DelimitierOfSmallOrEqual = "<=";
  string DelimitierOfSmall = "<";
  string DelimitierOfBig = ">";
  string DelimitierOfNotEqual = "!=";
  int os = -1;

  size_t posOfAllText = 0;
  string tokenOfFirsExpression, tokenOfSecondExpression;
  //case for "=="
  if ((posOfAllText = stringOfCondition.find(DelimitierOfEqual)) != string::npos) {

    tokenOfFirsExpression = stringOfCondition.substr(0, posOfAllText);
    tokenOfSecondExpression = stringOfCondition.substr(posOfAllText + 2, stringOfCondition.size() - 1);
    stringOfCondition.erase(0, posOfAllText + stringOfCondition.length());
    os = 1;
  }
    //case for ">="
  else if ((posOfAllText = stringOfCondition.find(DelimitierOfBigOrEqual)) != string::npos) {

    tokenOfFirsExpression = stringOfCondition.substr(0, posOfAllText);
    tokenOfSecondExpression = stringOfCondition.substr(posOfAllText + 2, stringOfCondition.size() - 1);
    stringOfCondition.erase(0, posOfAllText + stringOfCondition.length());
    os = 2;
  }
    //case for "<="
  else if ((posOfAllText = stringOfCondition.find(DelimitierOfSmallOrEqual)) != string::npos) {
    tokenOfFirsExpression = stringOfCondition.substr(0, posOfAllText);
    tokenOfSecondExpression = stringOfCondition.substr(posOfAllText + 2, stringOfCondition.size() - 1);
    stringOfCondition.erase(0, posOfAllText + stringOfCondition.length());
    os = 3;
  }
    //case for "!="
  else if ((posOfAllText = stringOfCondition.find(DelimitierOfNotEqual)) != string::npos) {
    tokenOfFirsExpression = stringOfCondition.substr(0, posOfAllText);
    tokenOfSecondExpression = stringOfCondition.substr(posOfAllText + 2, stringOfCondition.size() - 1);
    stringOfCondition.erase(0, posOfAllText + stringOfCondition.length());
    os = 4;
  }
    //case for "<"
  else if ((posOfAllText = stringOfCondition.find(DelimitierOfSmall)) != string::npos) {
    tokenOfFirsExpression = stringOfCondition.substr(0, posOfAllText);
    tokenOfSecondExpression = stringOfCondition.substr(posOfAllText + 1, stringOfCondition.size() - 1);
    stringOfCondition.erase(0, posOfAllText + stringOfCondition.length());
    os = 5;
  }
    //case for ">"
  else if ((posOfAllText = stringOfCondition.find(DelimitierOfBig)) != string::npos) {
    tokenOfFirsExpression = stringOfCondition.substr(0, posOfAllText);
    tokenOfSecondExpression = stringOfCondition.substr(posOfAllText + 1, stringOfCondition.size() - 1);
    stringOfCondition.erase(0, posOfAllText + stringOfCondition.length());
    os = 6;
  }
  switch (os) {
    case 1:
      if (Variables::getInstance()->doShuntingYard(tokenOfFirsExpression)
          == Variables::getInstance()->doShuntingYard(tokenOfSecondExpression))
        return true;
      break;
    case 2:
      if (Variables::getInstance()->doShuntingYard(tokenOfFirsExpression)
          >= Variables::getInstance()->doShuntingYard(tokenOfSecondExpression))
        return true;
      break;
    case 3:
      if (Variables::getInstance()->doShuntingYard(tokenOfFirsExpression)
          <= Variables::getInstance()->doShuntingYard(tokenOfSecondExpression))
        return true;
      break;
    case 4:
      if (Variables::getInstance()->doShuntingYard(tokenOfFirsExpression)
          != Variables::getInstance()->doShuntingYard(tokenOfSecondExpression))
        return true;
      break;
    case 5:
      if (Variables::getInstance()->doShuntingYard(tokenOfFirsExpression)
          < Variables::getInstance()->doShuntingYard(tokenOfSecondExpression))
        return true;
      break;
    case 6:
      if (Variables::getInstance()->doShuntingYard(tokenOfFirsExpression)
          > Variables::getInstance()->doShuntingYard(tokenOfSecondExpression))
        return true;
      break;
    default:break;
  }
  return false;

}

