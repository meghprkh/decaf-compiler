#include <stdio.h>
#include <cstdlib>
#include <string>

class Base {
public:
  virtual void print() = 0;
};

class Literal: public Base {
public:
  virtual void print() = 0;
};

class IntLiteral: public Literal {
public:
  IntLiteral(const char *x) {
    value = atoi(x);
  }
  void print() {
    printf("%d", value);
  }
private:
  int value;
};

enum class OpType { add, subtract, multiply, divide };

class BinExpr: public Base {
public:
  BinExpr(Base* l1, OpType o, Base* l2) {
    left = l1;
    op = o;
    right = l2;
  }
  void print() {
    left->print();
    switch (op) {
      case OpType::add : printf("+"); break;
      case OpType::subtract : printf("-"); break;
      case OpType::multiply : printf("*"); break;
      case OpType::divide : printf("/"); break;
    }
    right->print();
  }
private:
  Base* left;
  OpType op;
  Base* right;
};

union Node {
  Base* b;
  char* token;
};

typedef union Node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1
