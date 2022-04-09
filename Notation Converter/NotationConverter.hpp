/*
Names: Osama Bin Basit(driver)    Chen-Yu Liu(navigator)
UID:         U39050886                  U39755333
Weightage:     50-50
*/

#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "NotationConverterInterface.hpp"
#include"Deque.hpp"

class NotationConverter: public NotationConverterInterface{

public:
  
  std::string postfixToInfix(std::string inStr);
  std::string postfixToPrefix(std::string inStr);

  std::string infixToPostfix(std::string inStr);
  std::string infixToPrefix(std::string inStr);

  std::string prefixToInfix(std::string inStr);
  std::string prefixToPostfix(std::string inStr);

  int evaluatePrecedence(char c); //determines the priority of the operator
  std::string removeSpaces(std::string str); //returns a string with no spcaes in it
  std::string stringFormat(std::string str); //returns a string with spaces in result as required
  void checkBad(std::string str); //checks for exceptions
};

#endif


