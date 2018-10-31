#include "base.hpp"
#include "literals.hpp"
#include "exprs.hpp"
#include "locations.hpp"
#include "calls.hpp"
#include "field_decls.hpp"
#include "var_decls.hpp"

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
  StringLiteral* string_literal;
  MethodArgsList* method_args;
  CalloutArgsList* callout_args;
  char* token;
};

typedef union Node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1
