#pragma once

#include "base.hpp"
#include "literals.hpp"
#include "exprs.hpp"
#include "locations.hpp"
#include "calls.hpp"
#include "field_decls.hpp"
#include "var_decls.hpp"
#include "statements.hpp"
#include "method_decls.hpp"


class Program: public Base {
public:
  Program(FieldDecls* _field_decls, MethodDecls* _method_decls);
  int print();
  void traverse();
  llvm::Value* codegen();
private:
  FieldDecls* field_decls;
  MethodDecls* method_decls;
};

union Node {
  Base* base;
  Expr* expr;
  Type type;
  FieldDecls* field_decls;
  FieldDecl* field_decl;
  FieldDeclArgs* field_decl_args;
  VarDecls* var_decls;
  VarDecl* var_decl;
  VarDeclVars* var_decl_vars;

  MethodDecl* method_decl;
  MethodDecls* method_decls;
  MethodDeclArg* method_decl_arg;
  MethodDeclArgs* method_decl_args;

  Block* block;
  Statement* statement;
  StatementsList* statements;
  AssignOp assign_op;

  StringLiteral* string_literal;
  MethodArgsList* method_args;
  CalloutArgsList* callout_args;
  char* token;
};

typedef union Node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1
