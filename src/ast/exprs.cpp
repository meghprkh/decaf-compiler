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

void ArithExpr::traverse() {
  l->traverse();
  r->traverse();
  if (l->get_type() != Type::_int)
    ERROR(12, "left subexpr not of type int");
  if (r->get_type() != Type::_int)
    ERROR(12, "right subexpr not of type int");
}

void RelExpr::traverse() {
  l->traverse();
  r->traverse();
  if (l->get_type() != Type::_int)
    ERROR(12, "left subexpr of relop not of type int");
  if (r->get_type() != Type::_int)
    ERROR(12, "right subexpr of relop not of type int");
}

void EqExpr::traverse() {
  l->traverse();
  r->traverse();
  if (l->get_type() != r->get_type())
    ERROR(13, "eqop types dont match " +
                                typeToString(l->get_type()) + " != " +
                                typeToString(r->get_type())
                            );
}

void CondExpr::traverse() {
  l->traverse();
  r->traverse();
  if (l->get_type() != Type::_boolean)
    ERROR(14, "left subexpr of condop not of type boolean");
  if (r->get_type() != Type::_boolean)
    ERROR(14, "right subexpr of condop not of type boolean");
}

void UnaryMinusExpr::traverse() {
  e->traverse();
}

void UnaryNotExpr::traverse() {
  e->traverse();
  if (e->get_type() != Type::_boolean)
    ERROR(14, "unary not's expr is not of type boolean");
}

void ParenthizedExpr::traverse() {
  e->traverse();
}

llvm::Value* ArithExpr::codegen() {
  llvm::Value *left = l->codegen();
  llvm::Value *right = r->codegen();
  llvm::Value *v = nullptr;
  switch (op) {
    case ArithOp::add : v = mllvm->Builder->CreateAdd(left, right, "addexpr"); break;
    case ArithOp::sub : v = mllvm->Builder->CreateSub(left, right, "subexpr"); break;
    case ArithOp::mul : v = mllvm->Builder->CreateMul(left, right, "mulexpr"); break;
    case ArithOp::div : v = mllvm->Builder->CreateSDiv(left, right, "divexpr"); break;
    case ArithOp::mod : v = mllvm->Builder->CreateSRem(left, right, "modexpr"); break;
  }
  return v;
}

llvm::Value* RelExpr::codegen() {
  llvm::Value *left = l->codegen();
  llvm::Value *right = r->codegen();
  llvm::Value *v = nullptr;
  switch (op) {
    case RelOp::lt : v = mllvm->Builder->CreateICmpSLT(left, right, "ltexpr"); break;
    case RelOp::gt : v = mllvm->Builder->CreateICmpSGT(left, right, "gtexpr"); break;
    case RelOp::le : v = mllvm->Builder->CreateICmpSLE(left, right, "leexpr"); break;
    case RelOp::ge : v = mllvm->Builder->CreateICmpSGE(left, right, "geexpr"); break;
  }
  return v;
}

llvm::Value* EqExpr::codegen() {
  llvm::Value *left = l->codegen();
  llvm::Value *right = r->codegen();
  llvm::Value *v = nullptr;
  switch (op) {
    case EqOp::eq : v = mllvm->Builder->CreateICmpEQ(left, right, "eqexpr"); break;
    case EqOp::ne : v = mllvm->Builder->CreateICmpNE(left, right, "neexpr"); break;
  }
  return v;
}

llvm::Value* CondExpr::codegen() {
  llvm::Value *left = l->codegen();
  llvm::Value *right = r->codegen();
  llvm::Value *v = nullptr;
  switch (op) {
    case CondOp::_and : v = mllvm->Builder->CreateAnd(left, right, "andexpr"); break;
    case CondOp::_or : v = mllvm->Builder->CreateOr(left, right, "orexpr"); break;
  }
  return v;
}

llvm::Value* UnaryMinusExpr::codegen() {
  llvm::Value* v = e->codegen();
  return mllvm->Builder->CreateNeg(v, "negexpr");
}

llvm::Value* UnaryNotExpr::codegen() {
  llvm::Value* v = e->codegen();
  return mllvm->Builder->CreateNot(v, "notexpr");
}

llvm::Value* ParenthizedExpr::codegen() {
  return e->codegen();
}
