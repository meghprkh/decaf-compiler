#include "field_decls.hpp"

void FieldDeclArgs::add(const char *_id) {
  vars.push_front(string(_id));
}

void FieldDeclArgs::add(const char *_id, const char *_index) {
  auto p = make_pair(string(_id), atoi(_index));
  if (p.second <= 0)
    ERROR(4, _id + string("\'s IntLiteral is ") + _index + "<= 0");
  arrs.push_front(p);
}

int FieldDeclArgs::print() {
  printText("FieldDeclArgs");
  int p = pidcount;
  for (auto v: vars) {
    int _v = printText(v);
    printRelation(p, _v);
  }
  for (auto a: arrs) {
    int _a = printText(a.first + ":arr:" + to_string(a.second));
    printRelation(p, _a);
  }
  return p;
}

FieldDecl::FieldDecl(Type _type, FieldDeclArgs* _args) {
  type = _type;
  args = _args;
}

int FieldDecl::print() {
  int _args = args->print();
  printText(typeToString(type) + ":FieldDecl");
  printRelation(_args);
  return pidcount;
}

void FieldDecls::add(FieldDecl* _f) {
  list.push_back(_f);
}

int FieldDecls::print() {
  printText("FieldDecls");
  int p = pidcount;
  for (auto f: list) {
    int _f = f->print();
    printRelation(p, _f);
  }
  return p;
}

void FieldDeclArgs::traverse() {
  throw runtime_error("FieldDeclArgs traverse without type arg called!");
}

void FieldDeclArgs::traverse(Type type) {
  for (auto v: vars) {
    CONTEXT_INSERT(v, CtxDataType(LocationType::var, v, type));
  }
  for (auto a: arrs) {
    CONTEXT_INSERT(a.first, CtxDataType(LocationType::arr, a.first, type, a.second));
  }
}

void FieldDecl::traverse() {
  args->traverse(type);
}

void FieldDecls::traverse() {
  for (auto f: list) f->traverse();
}
