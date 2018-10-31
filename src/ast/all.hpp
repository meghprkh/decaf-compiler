#include "base.hpp"
#include "literals.hpp"
#include "exprs.hpp"
#include "locations.hpp"
#include "calls.hpp"

union Node {
  Base* base;
  Expr* expr;
  StringLiteral* string_literal;
  MethodArgsList* method_args;
  CalloutArgsList* callout_args;
  char* token;
};

typedef union Node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1
