#include "base.hpp"

class VarDeclVars: public Base {
public:
  VarDeclVars() {};
  void add(const char *_v);
  int print();
private:
  deque<string> vars;
};

class VarDecl: public Base {
public:
  VarDecl(Type _type, VarDeclVars* _vars);
  int print();
private:
  Type type;
  VarDeclVars* vars;
};

class VarDecls: public Base {
public:
  VarDecls() {};
  void add(VarDecl *_v);
  int print();
private:
  deque<VarDecl*> list;
};
