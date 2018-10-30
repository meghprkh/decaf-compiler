#include "base.hpp"

enum class ArithOp { add, sub, mul, div, mod };
enum class RelOp   { lt, gt, le, ge };
enum class EqOp    { eq, ne };
enum class CondOp  { _and, _or };

class ArithExpr: public Expr {
public:
  ArithExpr(Expr* _l, ArithOp _op, Expr* _r);
  int print();
private:
  Expr *l, *r;
  ArithOp op;
};

class RelExpr: public Expr {
public:
  RelExpr(Expr* _l, RelOp _op, Expr* _r);
  int print();
private:
  Expr *l, *r;
  RelOp op;
};

class EqExpr: public Expr {
public:
  EqExpr(Expr* _l, EqOp _op, Expr* _r);
  int print();
private:
  Expr *l, *r;
  EqOp op;
};

class CondExpr: public Expr {
public:
  CondExpr(Expr* _l, CondOp _op, Expr* _r);
  int print();
private:
  Expr *l, *r;
  CondOp op;
};

class UnaryMinusExpr: public Expr {
public:
  UnaryMinusExpr(Expr* _e);
  int print();
private:
  Expr* e;
};

class UnaryNotExpr: public Expr {
public:
  UnaryNotExpr(Expr* _e);
  int print();
private:
  Expr* e;
};

class ParenthizedExpr: public Expr {
public:
  ParenthizedExpr(Expr* _e);
  int print();
private:
  Expr* e;
};
