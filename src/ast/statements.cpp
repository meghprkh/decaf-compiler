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

int loop_depth = 0;

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

string curMethodName;
bool curMethodReturnVoid;
Type curMethodReturnType;
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
    ERROR(15, "AssignStatement type mismatch : " +
                                location->get_id() + " | " +
                                typeToString(location->get_type()) + " != " +
                                typeToString(expr->get_type())
                              );
  }
  if ((op == AssignOp::pe || op == AssignOp::me) && location->get_type() != Type::_int) {
    ERROR(16, location->get_id() + " not of type int");
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
    ERROR(11, "if cannot have condition of type " + typeToString(condition->get_type()));
  }
}

void LoopStatement::traverse() {
  loop_depth++;
  context.newContext();
  CONTEXT_INSERT(id, CtxDataType(LocationType::var, id, Type::_int));
  from->traverse();
  to->traverse();
  b->traverse();
  if (from->get_type() != Type::_int)
    ERROR(17, "from expr of LoopStatement not of type int");
  if (to->get_type() != Type::_int)
    ERROR(17, "to expr of LoopStatement not of type int");
  context.popContext();
  loop_depth--;
}

void ReturnStatement::traverse() {
  if (e) e->traverse();
  if (!curMethodReturnVoid) {
    if (!e)
      ERROR(8, curMethodName + " cannot have void return");
    else if (e->get_type() != curMethodReturnType)
      ERROR(8, curMethodName + " cannot have return type " + typeToString(e->get_type()));
  } else {
    if (e) ERROR(7, curMethodName + " shall not have return body");
  }
}

void BreakStatement::traverse() {
  if (loop_depth <= 0) ERROR(18, "break outside loop");
}

void ContinueStatement::traverse() {
  if (loop_depth <= 0) ERROR(18, "continue outside loop");
}



bool StatementsList::isReturn() {
  for (auto s: list) if (s->isReturn()) return true;
  return false;
}

bool Block::isReturn() {
  return list->isReturn();
}

bool AssignStatement::isReturn() {
  return false;
}

bool MethodCallStatement::isReturn() {
  return false;
}

bool IfStatement::isReturn() {
  return false;
}

bool LoopStatement::isReturn() {
  return false;
}

bool ReturnStatement::isReturn() {
  return true;
}

bool BreakStatement::isReturn() {
  return true;
}

bool ContinueStatement::isReturn() {
  return true;
}



llvm::Value* StatementsList::codegen() {
  llvm::Value* v;
  for (auto s: list) {
    v = s->codegen();
    if (s->isReturn()) break;
  }
  return v;
}

llvm::Value* Block::codegen() {
  mllvm->ctx->newContext();
  var_decls->codegen();
  llvm::Value* v = list->codegen();
  mllvm->ctx->popContext();
  return v;
}

llvm::Value* AssignStatement::codegen() {
  auto lhs = location->get_id();
  auto rhs = expr->codegen();

  auto val = op == AssignOp::eq ? rhs : mllvm->ctx->load(lhs);

  switch (op) {
    case AssignOp::eq :
      break;
    case AssignOp::pe :
      val = mllvm->Builder->CreateAdd(val, rhs, "assignStatement:pe");
      break;
    case AssignOp::me :
      val = mllvm->Builder->CreateSub(val, rhs, "assignStatement:me");
      break;
  }
  return mllvm->ctx->update(lhs, val);
}

llvm::Value* MethodCallStatement::codegen() {
  return method_call->codegen();
}

llvm::Value* IfStatement::codegen() {
  auto conditionV = condition->codegen();
  auto ifBB = mllvm->getBasicBlock("if");
  auto elseBB = mllvm->getBasicBlock("else");
  auto mergeBB = mllvm->getBasicBlock("ifcont");
  mllvm->currentFn->getBasicBlockList().push_back(ifBB);
  mllvm->currentFn->getBasicBlockList().push_back(elseBB);
  mllvm->currentFn->getBasicBlockList().push_back(mergeBB);

  mllvm->Builder->CreateCondBr(conditionV, ifBB, elseBB);

  // Emit if block
  mllvm->Builder->SetInsertPoint(ifBB);
  auto ifV = if_true->codegen();
  if (!if_true->isReturn()) mllvm->Builder->CreateBr(mergeBB);

  mllvm->Builder->SetInsertPoint(elseBB);
  if (if_false) {
    // Emit else block.
    auto elseV = if_false->codegen();
    if (!if_false->isReturn()) mllvm->Builder->CreateBr(mergeBB);
  } else {
    mllvm->Builder->CreateBr(mergeBB);
  }

  // Emit merge block.
  mllvm->Builder->SetInsertPoint(mergeBB);
  return mergeBB;
}

llvm::Value* LoopStatement::codegen() {
  mllvm->ctx->newContext();
  mllvm->ctx->insert(id, Type::_int);
  mllvm->ctx->update(id, from->codegen());
  auto step = (Expr*) new IntLiteral("1");

  auto conditionBB = mllvm->getBasicBlock("loopCondition");
  auto bodyBB = mllvm->getBasicBlock("loopBody");
  auto afterBB = mllvm->getBasicBlock("loopAfter");
  mllvm->currentFn->getBasicBlockList().push_back(bodyBB);
  mllvm->currentFn->getBasicBlockList().push_back(afterBB);
  auto loopvar = (Location*) new VarLocation(id.c_str());

  MLLVMLoopInfo loopinfo = {loopvar, conditionBB, bodyBB, afterBB};
  mllvm->loops.push(loopinfo);

  auto start = new AssignStatement(loopvar, AssignOp::eq, from);
  start->codegen();

  mllvm->Builder->CreateBr(conditionBB);
  mllvm->Builder->SetInsertPoint(conditionBB);
  auto condition = new RelExpr((Expr*) loopvar, RelOp::lt, to);
  auto conditionV = condition->codegen();

  mllvm->Builder->CreateCondBr(conditionV, bodyBB, afterBB);

  mllvm->Builder->SetInsertPoint(bodyBB);
  b->codegen();
  if (!b->isReturn()) {
    auto increment = new AssignStatement(loopvar, AssignOp::pe, step);
    increment->codegen();
    mllvm->Builder->CreateBr(conditionBB);
  }

  mllvm->ctx->popContext();
  mllvm->loops.pop();

  mllvm->Builder->SetInsertPoint(afterBB);
  return afterBB;
}

llvm::Value* ReturnStatement::codegen() {
  if (e) return mllvm->Builder->CreateRet(e->codegen());
  else return mllvm->Builder->CreateRetVoid();
}

llvm::Value* BreakStatement::codegen() {
  mllvm->Builder->CreateBr(mllvm->loops.top().afterBB);
  return nullptr;
}

llvm::Value* ContinueStatement::codegen() {
  auto loop = mllvm->loops.top();

  auto step = (Expr*) new IntLiteral("1");
  auto increment = new AssignStatement(loop.loopvar, AssignOp::pe, step);
  increment->codegen();

  mllvm->Builder->CreateBr(loop.conditionBB);
  return nullptr;
}
