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

void ArithExpr::print() {
  l->print();
  printf(" ");
  switch (op) {
    case ArithOp::add : printf("+"); break;
    case ArithOp::sub : printf("-"); break;
    case ArithOp::mul : printf("*"); break;
    case ArithOp::div : printf("/"); break;
    case ArithOp::mod : printf("%%"); break;
  }
  printf(" ");
  r->print();
}

void RelExpr::print() {
  l->print();
  printf(" ");
  switch (op) {
    case RelOp::lt : printf("<"); break;
    case RelOp::gt : printf(">"); break;
    case RelOp::le : printf("<="); break;
    case RelOp::ge : printf(">="); break;
  }
  printf(" ");
  r->print();
}

void EqExpr::print() {
  l->print();
  printf(" ");
  switch (op) {
    case EqOp::eq : printf("=="); break;
    case EqOp::ne : printf("!="); break;
  }
  printf(" ");
  r->print();
}

void CondExpr::print() {
  l->print();
  printf(" ");
  switch (op) {
    case CondOp::_and : printf("&&"); break;
    case CondOp::_or : printf("||"); break;
  }
  printf(" ");
  r->print();
}
