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

void VarDeclVars::traverse() {
  throw runtime_error("VarDeclVars traverse without type arg called!");
}

void VarDeclVars::traverse(Type type) {
  for (auto v: vars) {
    CONTEXT_INSERT(v, CtxDataType(LocationType::var, v, type));
  }
}

void VarDecl::traverse() {
  vars->traverse(type);
}

void VarDecls::traverse() {
  // Add to current context. Dont create new context
  for (auto v: list) v->traverse();
}


llvm::Value* VarDeclVars::codegen() {
  return nullptr;
}

llvm::Value* VarDeclVars::codegen(Type type) {
  for (auto id: vars) mllvm->ctx->insert(id, type);
  return nullptr;
}

llvm::Value* VarDecl::codegen() {
  return vars->codegen(type);
}

llvm::Value* VarDecls::codegen() {
  for (auto v: list) v->codegen();
  return nullptr;
}
