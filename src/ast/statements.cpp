#include "statements.hpp"

void StatementsList::add(Statement* statement) {
  list.push_front(statement);
}

int StatementsList::print() {
  printText("StatementsList");
  int p = pidcount;
  for (auto s: list) {
    int _s = s->print();
    printRelation(p, _s);
  }
  return p;
}

Block::Block(VarDecls* _var_decls, StatementsList* _list) {
  var_decls = _var_decls;
  list = _list;
}

int Block::print() {
  int _v = var_decls->print();
  int _l = list->print();
  printText("Block");
  printRelation(_v);
  printRelation(_l);
  return pidcount;
}

AssignStatement::AssignStatement(Location* _location, AssignOp _op, Expr* _expr) {
  location = _location;
  op = _op;
  expr = _expr;
}

int AssignStatement::print() {
  int _l = location->print();
  int _e = expr->print();
  switch (op) {
    case AssignOp::eq : printText("=:AssignStatement"); break;
    case AssignOp::pe : printText("+=:AssignStatement"); break;
    case AssignOp::me : printText("-=:AssignStatement"); break;
  }
  printRelation(_l);
  printRelation(_e);
  return pidcount;
}

MethodCallStatement::MethodCallStatement(MethodCall* _method_call) {
  method_call = _method_call;
}

int MethodCallStatement::print() {
  int _m = method_call->print();
  printText("MethodCallStatement");
  printRelation(_m);
  return pidcount;
}

IfStatement::IfStatement(Expr* _condition, Block* _if_true, Block* _if_false) {
  condition = _condition;
  if_true = _if_true;
  if_false = _if_false;
}

int IfStatement::print() {
  int _c = condition->print();
  int _t = if_true->print();
  int _f = -1;
  if (if_false) _f = if_false->print();
  printText("IfStatement");
  printRelation(_c);
  printRelation(_t);
  if (if_false) printRelation(_f);
  return pidcount;
}

LoopStatement::LoopStatement(const char *_id, Expr* _from, Expr *_to, Block *_b) {
  id = string(_id);
  from = _from;
  to = _to;
  b = _b;
}

int LoopStatement::print() {
  int _from = from->print();
  int _to = to->print();
  int _b = b->print();
  printText(id + ":LoopStatement");
  printRelation(_from);
  printRelation(_to);
  printRelation(_b);
  return pidcount;
}

ReturnStatement::ReturnStatement(Expr* _e) {
  e = _e;
}

int ReturnStatement::print() {
  int _e = -1;
  if (e) _e = e->print();
  printText("ReturnStatement");
  if (e) printRelation(_e);
  return pidcount;
}

int BreakStatement::print() {
  printText("BreakStatement");
  return pidcount;
}

int ContinueStatement::print() {
  printText("ContinueStatement");
  return pidcount;
}

void StatementsList::traverse() {
  for (auto s: list) s->traverse();
}

void Block::traverse() {
  context.newContext();
  var_decls->traverse();
  list->traverse();
  context.popContext();
}

void AssignStatement::traverse() {
  location->traverse();
  expr->traverse();
  if (location->get_type() != expr->get_type()) {
    errors.push_back(Error(15, "AssignStatement type mismatch : " +
                                typeToString(location->get_type()) + " != " +
                                typeToString(expr->get_type())
                              ));
  }
}

void MethodCallStatement::traverse() {
  method_call->traverse();
}

void IfStatement::traverse() {
  condition->traverse();
  if_true->traverse();
  if (if_false) if_false->traverse();
  if (condition->get_type() != Type::_boolean) {
    errors.push_back(Error(11));
  }
}

void LoopStatement::traverse() {
  context.newContext();
  context.insert(id, CtxDataType(LocationType::var, id, Type::_int));
  from->traverse();
  to->traverse();
  b->traverse();
  if (from->get_type() != Type::_int)
    errors.push_back(Error(12, "from expr of LoopStatement not of type int"));
  if (to->get_type() != Type::_int)
    errors.push_back(Error(12, "to expr of LoopStatement not of type int"));
  context.popContext();
}

void ReturnStatement::traverse() {
  if (e) e->traverse();
  // XXX: check e type
}

void BreakStatement::traverse() {
  // XXX: Check if in loop
}

void ContinueStatement::traverse() {
  // XXX: Check if in loop
}
