#include "exprs.hpp"

ArithExpr::ArithExpr(Expr* _l, ArithOp _op, Expr* _r) {
  l = _l;
  op = _op;
  r = _r;
}

RelExpr::RelExpr(Expr* _l, RelOp _op, Expr* _r) {
  l = _l;
  op = _op;
  r = _r;
}

EqExpr::EqExpr(Expr* _l, EqOp _op, Expr* _r) {
  l = _l;
  op = _op;
  r = _r;
}

CondExpr::CondExpr(Expr* _l, CondOp _op, Expr* _r) {
  l = _l;
  op = _op;
  r = _r;
}

UnaryMinusExpr::UnaryMinusExpr(Expr* _e) {
  e = _e;
}

UnaryNotExpr::UnaryNotExpr(Expr* _e) {
  e = _e;
}

ParenthizedExpr::ParenthizedExpr(Expr* _e) {
  e = _e;
}

int ArithExpr::print() {
  int _l = l->print();
  int _r = r->print();
  switch (op) {
    case ArithOp::add : printText("+"); break;
    case ArithOp::sub : printText("-"); break;
    case ArithOp::mul : printText("*"); break;
    case ArithOp::div : printText("/"); break;
    case ArithOp::mod : printText("%%"); break;
  }
  printRelation(_l);
  printRelation(_r);
  return pidcount;
}

int RelExpr::print() {
  int _l = l->print();
  int _r = r->print();
  switch (op) {
    case RelOp::lt : printText("<"); break;
    case RelOp::gt : printText(">"); break;
    case RelOp::le : printText("<="); break;
    case RelOp::ge : printText(">="); break;
  }
  printRelation(_l);
  printRelation(_r);
  return pidcount;
}

int EqExpr::print() {
  int _l = l->print();
  int _r = r->print();
  switch (op) {
    case EqOp::eq : printText("=="); break;
    case EqOp::ne : printText("!="); break;
  }
  printRelation(_l);
  printRelation(_r);
  return pidcount;
}

int CondExpr::print() {
  int _l = l->print();
  int _r = r->print();
  switch (op) {
    case CondOp::_and : printText("&&"); break;
    case CondOp::_or : printText("||"); break;
  }
  printRelation(_l);
  printRelation(_r);
  return pidcount;
}

int UnaryMinusExpr::print() {
  int _e = e->print();
  printText("-");
  printRelation(_e);
  return pidcount;
}

int UnaryNotExpr::print() {
  int _e = e->print();
  printText("!");
  printRelation(_e);
  return pidcount;
}

int ParenthizedExpr::print() {
  int _e = e->print();
  printText("_");
  printRelation(_e);
  return pidcount;
}
