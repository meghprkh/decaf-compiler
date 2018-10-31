#pragma once

#include "base.hpp"
#include "literals.hpp"

class MethodArgsList: public Base {
public:
  MethodArgsList() {};
  void add(Expr* _e);
  int print();
private:
  deque<Expr*> list;
};

class MethodCall: public Expr {
public:
  MethodCall(const char *_fn, MethodArgsList* _args);
  int print();
private:
  string fn;
  MethodArgsList* args;
};

class CalloutArgsList: public Base {
public:
  CalloutArgsList() {};
  void add(Expr* s);
  void add(StringLiteral* s);
  int print();
private:
  deque<pair<Expr*, StringLiteral*> > list;
};

class Callout: public Expr {
public:
  Callout(const char *_fn, CalloutArgsList* _args);
  int print();
private:
  string fn;
  CalloutArgsList* args;
};
