#include "base.hpp"

class Literal: public Expr {
public:
  virtual int print() = 0;
};

class IntLiteral: public Literal {
public:
  IntLiteral(const char *x);
  int print();
private:
  int value;
};

class CharLiteral: public Literal {
public:
  CharLiteral(const char *x);
  int print();
private:
  char value;
};

class BoolLiteral: public Literal {
public:
  BoolLiteral(const char *x);
  int print();
private:
  bool value;
};

class StringLiteral: public Literal {
public:
  StringLiteral(const char *x);
  int print();
private:
  string value;
};
