#include "all.hpp"

Program::Program (FieldDecls* _field_decls, MethodDecls* _method_decls) {
  field_decls = _field_decls;
  method_decls = _method_decls;
}

int Program::print() {
  int _f = field_decls->print();
  int _m = method_decls->print();
  printText("Program");
  printRelation(_f);
  printRelation(_m);
  return pidcount;
}

void Program::traverse() {
  // XXX: create global context
  field_decls->traverse();
  method_decls->traverse();
}
