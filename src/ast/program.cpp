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
  context.newContext();
  field_decls->traverse();
  method_decls->traverse();
  auto cdt = CONTEXT_LOOKUP(string("main"));
  if (cdt.not_found) ERROR(3, "main not found");
  if (!cdt.method_args.empty()) ERROR(3, "main cannot take args");
}

llvm::Value* Program::codegen() {
  return nullptr;
}
