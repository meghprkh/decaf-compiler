#include "base.hpp"
#pragma once

class Literal: public Expr {
public:
  virtual int print() = 0;
  virtual Type get_type() = 0;
};

class IntLiteral: public Literal {
public:
  IntLiteral(const char *x);
  int print();
  Type get_type();
private:
  int value;
};

class CharLiteral: public Literal {
public:
  CharLiteral(const char *x);
  int print();
  Type get_type();
private:
  char value;
};

class BoolLiteral: public Literal {
public:
  BoolLiteral(const char *x);
  int print();
  Type get_type();
private:
  bool value;
};

class StringLiteral: public Literal {
public:
  StringLiteral(const char *x);
  int print();
  Type get_type();
private:
  string value;
};
