#pragma once

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

class Base {
public:
  virtual void print() = 0;
};

class Expr: public Base {
// Anything that can be evaluated
public:
  virtual void print() = 0;
};


union Node {
  Base* base;
  Expr* expr;
  char* token;
};

typedef union Node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1
