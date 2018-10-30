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
  printf("%d-->%d\n", pidcount, _l);
  printf("%d-->%d\n", pidcount, _r);
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
  printf("%d-->%d\n", pidcount, _l);
  printf("%d-->%d\n", pidcount, _r);
  return pidcount;
}

int EqExpr::print() {
  int _l = l->print();
  int _r = r->print();
  switch (op) {
    case EqOp::eq : printText("=="); break;
    case EqOp::ne : printText("!="); break;
  }
  printf("%d-->%d\n", pidcount, _l);
  printf("%d-->%d\n", pidcount, _r);
  return pidcount;
}

int CondExpr::print() {
  int _l = l->print();
  int _r = r->print();
  switch (op) {
    case CondOp::_and : printText("&&"); break;
    case CondOp::_or : printText("||"); break;
  }
  printf("%d-->%d\n", pidcount, _l);
  printf("%d-->%d\n", pidcount, _r);
  return pidcount;
}
