//
// Created by yoelsh on 07/11/2019.
//

#include "ShuntingYard.h"
#include <utility>
#include <cstring>
#include "regex"
#include "Var.h"
#include "Variables.h"
using namespace std;

Value::Value(const double va) : val(va) {}

Variable::Variable(string name1, double value1) : name(std::move(name1)), value(value1) {
  this->name = name1;
  this->value = value1;
}

BinaryOperator::BinaryOperator(Expression *left1, Expression *right1) : left(left1), right(right1) {
  this->right = right1;
  this->left = left1;
}

BinaryOperator::~BinaryOperator() {
  delete left;
  delete right;
}

UnaryOperator::UnaryOperator(Expression *exp1) : exp(exp1) {
  this->exp = exp1;
}

UnaryOperator::~UnaryOperator() {
  delete exp;
}

double Value::calculate() {
  return this->val;
}

double Variable::calculate() {
  return this->value;
}

Variable &Variable::operator++() {
  this->value++;
  return *this;
}

Variable &Variable::operator--() {
  this->value--;
  return *this;
}

Variable &Variable::operator+=(double d) {
  this->value += d;
  return *this;
}

Variable &Variable::operator-=(double d) {
  this->value -= d;
  return *this;
}

Variable &Variable::operator++(int) {
  this->value++;
  return *this;
}

Variable &Variable::operator--(int) {
  this->value--;
  return *this;
}

double Plus::calculate() {
  return this->left->calculate() + this->right->calculate();
}

Plus::Plus(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {
  this->right = right1;
  this->left = left1;
}

double Minus::calculate() {
  return this->left->calculate() - this->right->calculate();
}

Minus::Minus(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {
  this->right = right1;
  this->left = left1;
}

double Mul::calculate() {
  return this->left->calculate() * this->right->calculate();
}

Mul::Mul(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {
  this->right = right1;
  this->left = left1;
}

double Div::calculate() {
  if (this->right->calculate() == 0) {
    throw "division error";
  }
  return this->left->calculate() / this->right->calculate();
}

Div::Div(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {
  this->right = right1;
  this->left = left1;
}

double UPlus::calculate() {
  return this->exp->calculate();
}

UPlus::UPlus(Expression *exp1) : UnaryOperator(exp1) {
  this->exp = exp1;
}

double UMinus::calculate() {
  return -1 * this->exp->calculate();
}

UMinus::UMinus(Expression *exp1) : UnaryOperator(exp1) {
  this->exp = exp1;
}

Expression *Interpreter::interpret(string s) {
  // check input validity
  if (!inputIsValid(s) || s.length() == 0) {
    throw ("input is not valid");
  }

  //if input is valid - parse it and return an expression
  this->shuntingYard(s);

  return this->createExp();
}

bool Interpreter::inputIsValid(string s) {
  int countParenthesis = 0;

  // first we replace all vars in string in their value.
  // running on map reversely to check first longer vars (map is alredy sorted).
  for (auto iter = vars.rbegin(); iter != vars.rend(); ++iter) {
    s = regex_replace(s, regex(iter->first), to_string(iter->second));
  }

  // check operator and parenthesis validity
  for (unsigned i = 0; i < s.length(); ++i) {
    switch (s[i]) {
      case '(':countParenthesis++;     // count number of opening parentheis
        break;
      case ')':
        if (countParenthesis == 0) {    // if there's no opening parenthesis left then string is not valid
          return false;
        } else {
          countParenthesis--;
        }
        break;
      case '+':
      case '-':
        // check for unary expression validity
        if (i != 0 && !((s[i - 1] == '(') || isdigit(s[i - 1]))) {
          return false;
        } else if (i == 0 && (s[i + 1] == '-' || s[i + 1] == '+' || s[i + 1] == '*' || s[i + 1] == '/')) {
          return false;
        } else if (i == s.length() - 1) {
          return false;
        }
        break;
      case '*':
      case '/':
        if (i == 0 || s[i - 1] == '+' || s[i - 1] == '-' || s[i - 1] == '*' || s[i - 1] == '/') {
          return false;
        } else if (i == s.length() - 1) {
          return false;
        }
        break;
        // make sure that there are no letters and chars - only numbers, parenthesis and operators
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '.':     // handling fractions
        break;
      default:return false;   // every other char means there's an undefined var, so we reject
    }
  }
  // check if all parenthesis were closed
  if (countParenthesis != 0) {
    return false;
  }

  // no problem found; return true
  return true;
}

// parsing the string into postfix notation. data is held in members of class.
void Interpreter::shuntingYard(string s) {
  string tempDigits;
  string tempOperator;
  unsigned skip = 0;


  // parsing the string into postfix
  for (unsigned i = 0; i < s.length(); ++i) {
    // if token is digit or char - need to catch whole number or whole var
    if (isdigit(s[i]) || isalpha(s[i])) {
      unsigned j = i + 1;
      tempDigits = string(1, s[i]);
      // handling numbers with more than 1 digit or vars with more than 1 char
      while (isdigit(s[j]) || isalpha(s[j]) || s[j] == '_' || s[j] == '.') {
        tempDigits += s[j];
        j++;
        skip++;
      }
      this->q.push(tempDigits);  // pushing the number to the queue
      i += skip;
      skip = 0;
    } else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {    // if token is operator
      // if token is operator that could be unary
      if (s[i] == '+' || s[i] == '-') {
        // if not unary, check for operators with greater or equal precedence in stack
        if (!(i == 0 || s[i - 1] == '(')) {
          if (!this->operators.empty()) {
            tempOperator = this->operators.top();
            // every operator is of greater precedence
            //
            while (tempOperator[0] != '(') {
              this->q.push(tempOperator);
              this->operators.pop();
              if (!this->operators.empty()) {
                tempOperator = this->operators.top();
              }
                // no operators left, make while loop stop
              else {
                tempOperator[0] = '(';
              }
            }
          }
        }
      }
        // if token could not be unary - check for greater precedence
      else if (s[i] == '*' || s[i] == '/') {
        if (!this->operators.empty()) {
          tempOperator = this->operators.top();
          while (tempOperator[0] == '~' || tempOperator[0] == '&') {
            this->q.push(tempOperator);
            this->operators.pop();
            if (!this->operators.empty())
              tempOperator = this->operators.top();
            else
              tempOperator = "";
          }
        }
      }

      // now push the operator. first check if unary and push the appropriate operator
      if (s[i] == '+' || s[i] == '-') {
        if (i == 0 || s[i - 1] == '(') {
          if (s[i] == '-') {
            this->operators.push(string(1, '~'));
          } else {
            this->operators.push(string(1, '&'));
          }
        } else {
          this->operators.push(string(1, s[i])); // put the operator in the operators stack
        }
      } else {
        this->operators.push(string(1, s[i])); // put the operator in the operators stack
      }
    } else if (s[i] == '(') {   // if token is left parenthesis
      this->operators.push(string(1, s[i])); // put the parenthesis in the queue
    } else if (s[i] == ')') {   // if token is right parenthesis
      //copying the last operator
      if (!this->operators.empty()) {
        tempOperator = this->operators.top();
      }
      // pop operators until reaching the opening parenthesis
      while (tempOperator[0] != '(') {
        this->operators.pop();  // pop the last operator from stack and push into queue
        this->q.push(tempOperator); // put the popped operator in the queue
        tempOperator = this->operators.top();  //copying the next operator
      }
      this->operators.pop();    // getting rid of the opening parenthesis
    }
  }

  // emptying the stack into the queue
  while (!this->operators.empty()) {
    tempOperator = this->operators.top();
    this->operators.pop();
    this->q.push(tempOperator);
  }
}

// parse queue into expression
Expression *Interpreter::createExp() {
  stack<Expression *> expStack;
  string token;
  Expression *temp1;
  Expression *temp2;

  while (!this->q.empty()) {
    token = this->q.front();
    if (isdigit(token[0])) {        // push numbers
      expStack.push(new Value(stod(token)));
    } else if (isalpha(token[0]) || token[0] == '_') {      // push variables
      expStack.push(new Variable(token, this->vars[token]));
    } else if (token[0] == '+') {
      temp1 = expStack.top();
      expStack.pop();
      temp2 = expStack.top();
      expStack.pop();
      expStack.push(new Plus(temp2, temp1));
    } else if (token[0] == '-') {
      temp1 = expStack.top();
      expStack.pop();
      temp2 = expStack.top();
      expStack.pop();
      expStack.push(new Minus(temp2, temp1));
    } else if (token[0] == '/') {
      temp1 = expStack.top();
      expStack.pop();
      temp2 = expStack.top();
      expStack.pop();
      expStack.push(new Div(temp2, temp1));
    } else if (token[0] == '*') {
      temp1 = expStack.top();
      expStack.pop();
      temp2 = expStack.top();
      expStack.pop();
      expStack.push(new Mul(temp2, temp1));
    } else if (token[0] == '&') {   // uplus
      temp1 = expStack.top();
      expStack.pop();
      expStack.push(new UPlus(temp1));
    } else if (token[0] == '~') {   // uminus
      temp1 = expStack.top();
      expStack.pop();
      expStack.push(new UMinus(temp1));
    }

    this->q.pop();
  }

  return expStack.top();
}

void Interpreter::setVariables(string vars1) {

  // based on code from stack overflow :
  // https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
  string delimiter = ";";
  size_t pos = 0;
  string token;

  // isolate every var and send it to another function to insert it
  while ((pos = vars1.find(delimiter)) != string::npos) {
    token = vars1.substr(0, pos);
    generateVarAndVal(token);
    vars1.erase(0, pos + delimiter.length());
  }
  // generate last token. also handles case of only 1 token in string
  generateVarAndVal(vars1);
}

void Interpreter::generateVarAndVal(string token) {
  string var;
  string val;
  string delimiter = "=";
  size_t pos = 0;
  bool pointFound = false;

  // check if there's a "=" in the string
  if ((pos = token.find(delimiter)) == string::npos) {
    throw ("variable string not valid");
  }

  // splitting the string by the delimiter
  var = token.substr(0, pos);
  val = token.erase(0, pos + delimiter.length());
  //remove_if(var.begin(),var.end(),' ');
  //remove_if(val.begin(),val.end(),' ');
  // check var validity
  if (isdigit(var[0]) || var[0] == '_') {
    throw ("variable string not valid");
  }

  for (unsigned i = 1; i < var.length(); ++i) {
    if (!(isalpha(var[i]) || isdigit(var[i]) || var[i] == '_')) {
      throw ("variable string not valid");
    }
  }


  // check val validity. only numbers and one point are acceptable
  // (and the point can't be at the beginning of th value)
  for (unsigned i = 0; i < val.length(); ++i) {
    if (val[i] == '.') {
      if (!pointFound && i != 0) {
        pointFound = true;
        continue;
      } else {
        throw ("value string not valid");
      }
    } else if (val[i] == '-' && i == 0) {
      continue;
    } else if (!isdigit(val[i])) {
      throw ("value string not valid");
    }
  }

  if (this->vars.count(var)) {
    this->vars.erase(var);
  }
  //add the new var to the map!
  this->vars.insert(pair<string, double>(var, stod(val)));
  if (Variables::getInstance()->UpdateValueOfProgramVar(var, Variables::getInstance()->doShuntingYard(val))) {
    Variables::getInstance()->UpdateValueOfProgramVar(var, Variables::getInstance()->doShuntingYard(val));
    Variables::getInstance()->InsertToQueOfVarsToPushToTheServer(Variables::getInstance()->programMap[var]);
  }
}
map<string, double> Interpreter::GetVars() {
  return vars;
}
void Interpreter::setVariables(string varName, double val) {
  vars[varName] = val;
}