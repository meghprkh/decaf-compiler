#include "var_decls.hpp"

void VarDeclVars::add(const char *_v) {
  vars.push_front(string(_v));
}

int VarDeclVars::print() {
  printText("VarDeclVars");
  int p = pidcount;
  for (auto v: vars) {
    int _v = printText(v);
    printRelation(p, _v);
  }
  return p;
}

VarDecl::VarDecl(Type _type, VarDeclVars* _vars) {
  type = _type;
  vars = _vars;
}

int VarDecl::print() {
  int _vars = vars->print();
  printText(typeToString(type) + ":VarDecl");
  printRelation(_vars);
  return pidcount;
}

void VarDecls::add(VarDecl *_v) {
  list.push_front(_v);
}

int VarDecls::print() {
  printText("VarDecls");
  int p = pidcount;
  for (auto v: list) {
    int _v = v->print();
    printRelation(p, _v);
  }
  return p;
}