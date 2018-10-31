#pragma once

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

class Base {
public:
  virtual int print() = 0;
};

class Expr: public Base {
// Anything that can be evaluated
public:
  virtual int print() = 0;
};


union Node {
  Base* base;
  Expr* expr;
  char* token;
};

typedef union Node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1

extern int pidcount;
void printText(int v);
void printText(char v);
void printText(const char *v);
void printText(string v);
void printRelation(int from, int to);
void printRelation(int to);
