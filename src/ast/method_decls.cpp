#include "method_decls.hpp"

MethodDeclArg::MethodDeclArg(Type _type, const char *_id) {
  type = _type;
  id = string(_id);
}

int MethodDeclArg::print() {
  printText(typeToString(type) + ":" + id + ":MethodDeclArg");
  return pidcount;
}

void MethodDeclArgs::add(MethodDeclArg* arg) {
  args.push_front(arg);
}

int MethodDeclArgs::print() {
  printText("MethodDeclArgs");
  int p = pidcount;
  for (auto a: args) {
    int _a = a->print();
    printRelation(p, _a);
  }
  return p;
}

MethodDecl::MethodDecl(Type _type, const char *_id, MethodDeclArgs* _args, Block* _block) {
  isVoid = false;
  type = _type;
  id = string(_id);
  args = _args;
  block = _block;
}

MethodDecl::MethodDecl(const char *_id, MethodDeclArgs* _args, Block* _block) {
  isVoid = true;
  id = string(_id);
  args = _args;
  block = _block;
}

int MethodDecl::print() {
  int _a = args->print();
  int _b = block->print();
  string _t = isVoid ? "void" : typeToString(type);
  printText(_t + ":" + id + ":MethodDecl");
  printRelation(_a);
  printRelation(_b);
  return pidcount;
}

void MethodDecls::add(MethodDecl* method_decl) {
  list.push_front(method_decl);
}

int MethodDecls::print() {
  printText("MethodDecls");
  int p = pidcount;
  for (auto m: list) {
    int _m = m->print();
    printRelation(p, _m);
  }
  return p;
}

void MethodDeclArg::traverse() {
  context.insert(id, CtxDataType(LocationType::var, id, type));
}

void MethodDeclArgs::traverse() {
  for (auto a: args) a->traverse();
}

vector<Type> MethodDeclArgs::get_types() {
  vector<Type> toret;
  for (auto a: args) toret.push_back(a->get_type());
  return toret;
}

void MethodDecl::traverse() {
  auto cdt = CtxDataType(LocationType::method, id, type);
  cdt.isVoid = isVoid;
  cdt.method_args = args->get_types();
  context.insert(id, cdt);

  curMethodName = id;
  curMethodReturnVoid = isVoid;
  curMethodReturnType = type;

  context.newContext();
  args->traverse();
  block->traverse();
}

void MethodDecls::traverse() {
  for (auto m: list) m->traverse();
}
