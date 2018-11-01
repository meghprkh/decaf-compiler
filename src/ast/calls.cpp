#include "calls.hpp"

MethodCall::MethodCall(const char *_fn, MethodArgsList* _args) {
  fn = string(_fn);
  args = _args;
}

Callout::Callout(const char *_fn, CalloutArgsList* _args) {
  fn = string(_fn);
  args = _args;
}

void MethodArgsList::add(Expr *_e) {
  list.push_front(_e);
}

void CalloutArgsList::add(Expr *_e) {
  list.push_front(make_pair(_e, (StringLiteral*) NULL));
}

void CalloutArgsList::add(StringLiteral *_s) {
  list.push_front(make_pair((Expr*) NULL, _s));
}

int MethodCall::print() {
  int _args = args->print();
  printText(fn);
  printRelation(_args);
  return pidcount;
}

int MethodArgsList::print() {
  printText("MethodArgsList");
  int p = pidcount;
  for (auto e: list) {
    int _e = e->print();
    printRelation(p, _e);
  }
  return p;
}

int Callout::print() {
  int _args = args->print();
  printText(fn + ":callout");
  printRelation(_args);
  return pidcount;
}

int CalloutArgsList::print() {
  printText("CalloutArgsList");
  int p = pidcount;
  for (auto etmp: list) {
    auto e = etmp.first ? etmp.first : etmp.second;
    int _e = e->print();
    printRelation(p, _e);
  }
  return p;
}

Type MethodCall::get_type() {
  return context.lookup(fn).type;
}

void MethodArgsList::traverse() {
  for (auto e: list) {
    e->traverse();
  }
}

void MethodCall::traverse() {
  args->traverse();
}

void CalloutArgsList::traverse() {
  for (auto e: list) {
    if (e.first) e.first->traverse();
    else e.second->traverse();
  }
}

void Callout::traverse() {
  args->traverse();
}
