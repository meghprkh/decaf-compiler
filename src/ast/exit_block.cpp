#include "exit_block.hpp"

Block* get_exit_block(CalloutArgsList* debug_callout_args) {
  auto debug_callout = new Callout("printf", debug_callout_args);
  auto debug_callout_stmt = new MethodCallStatement((MethodCall*) debug_callout);
  auto callout_args = new CalloutArgsList();
  callout_args->add(new IntLiteral("1"));
  auto callout = new Callout("exit", callout_args);
  auto callout_stmt = new MethodCallStatement((MethodCall*) callout);
  auto stmt_list = new StatementsList();
  stmt_list->add(callout_stmt);
  stmt_list->add(debug_callout_stmt);
  auto block = new Block(new VarDecls(), stmt_list);
  return block;
}

Base* get_conditional_exit(Expr* condition, CalloutArgsList* debug_callout_args) {
  return new IfStatement(condition, get_exit_block(debug_callout_args));
}
