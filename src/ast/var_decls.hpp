#include "base.hpp"
#pragma once

class VarDeclVars: public Base {
public:
  VarDeclVars() {};
  void add(const char *_v);
  int print();
  void traverse();
  void traverse(Type type);
private:
  deque<string> vars;
};

class VarDecl: public Base {
public:
  VarDecl(Type _type, VarDeclVars* _vars);
  int print();
  void traverse();
private:
  Type type;
  VarDeclVars* vars;
};

class VarDecls: public Base {
public:
  VarDecls() {};
  void add(VarDecl *_v);
  int print();
  void traverse();
private:
  deque<VarDecl*> list;
};
