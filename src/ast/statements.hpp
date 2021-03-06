#pragma once

#include "base.hpp"
#include "var_decls.hpp"
#include "calls.hpp"
#include "literals.hpp"
#include "locations.hpp"
#include "exprs.hpp"

class StatementsList: public Base {
public:
  StatementsList() {};
  void add(Statement* statement);
  int print();
  void traverse();
  llvm::Value* codegen();
  bool isReturn();
private:
  deque<Statement*> list;
};

class Block: public Statement {
// StatementsList with its own context
public:
  Block(VarDecls* _var_decls, StatementsList* _list);
  int print();
  void traverse();
  llvm::Value* codegen();
  bool isReturn();
private:
  VarDecls* var_decls;
  StatementsList* list;
};

enum class AssignOp { eq, pe, me };

class AssignStatement: public Statement {
public:
  AssignStatement(Location* _location, AssignOp _op, Expr* _expr);
  int print();
  void traverse();
  llvm::Value* codegen();
  bool isReturn();
private:
  Location* location;
  AssignOp op;
  Expr* expr;
};

class MethodCallStatement: public Statement {
public:
  MethodCallStatement(MethodCall* _method_call);
  int print();
  void traverse();
  llvm::Value* codegen();
  bool isReturn();
private:
  MethodCall* method_call;
};

class IfStatement: public Statement {
public:
  IfStatement(Expr* _condition, Block* _if_true, Block* _if_false = NULL);
  int print();
  void traverse();
  llvm::Value* codegen();
  bool isReturn();
private:
  Expr* condition;
  Block *if_true, *if_false;
};

extern int loop_depth;
class LoopStatement: public Statement {
public:
  LoopStatement(const char *_id, Expr* _from, Expr *_to, Block *_b);
  int print();
  void traverse();
  llvm::Value* codegen();
  bool isReturn();
private:
  string id;
  Expr *from, *to;
  Block *b;
};

extern string curMethodName;     // slightly dirty global vars
extern bool curMethodReturnVoid; // possible as this is imported
extern Type curMethodReturnType; // by method_decls.hpp

class ReturnStatement: public Statement {
public:
  ReturnStatement(Expr* _e = NULL);
  int print();
  void traverse();
  llvm::Value* codegen();
  bool isReturn();
private:
  Expr *e;
};

class BreakStatement: public Statement {
public:
  BreakStatement() {};
  int print();
  void traverse();
  llvm::Value* codegen();
  bool isReturn();
};

class ContinueStatement: public Statement {
public:
  ContinueStatement() {};
  int print();
  void traverse();
  llvm::Value* codegen();
  bool isReturn();
};
