#pragma once

#include "base.hpp"
#include "calls.hpp"
#include "literals.hpp"
#include "exprs.hpp"
#include "var_decls.hpp"
#include "statements.hpp"

Block* get_exit_block(CalloutArgsList* debug_callout_args);
Base* get_conditional_exit(Expr* condition, CalloutArgsList* debug_callout_args);
