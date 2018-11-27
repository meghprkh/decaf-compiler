#include "locations.hpp"
#include "statements.hpp"
#include "exit_block.hpp"

VarLocation::VarLocation(const char *_id) {
  id = string(_id);
}

ArrLocation::ArrLocation(const char *_id, Expr *_index) {
  id = string(_id);
  index = _index;
}

int VarLocation::print() {
  printText(id);
  return pidcount;
}

int ArrLocation::print() {
  int _index = index->print();
  printText(id + ":arr");
  printRelation(_index);
  return pidcount;
}

void VarLocation::traverse() {
  auto cdt = CONTEXT_LOOKUP(id);
  if (cdt.lt != LocationType::var && !cdt.not_found) {
    ERROR(9, id + " is not a variable");
  }
  type = cdt.type;
}

void ArrLocation::traverse() {
  auto cdt = CONTEXT_LOOKUP(id);
  if (cdt.lt != LocationType::arr && !cdt.not_found) {
    ERROR(10, id + " is not an array");
  }
  type = cdt.type;
}

llvm::Value* VarLocation::codegen() {
  return mllvm->ctx->lookup(id);
}

llvm::Value* ArrLocation::codegen() {
  auto _var = mllvm->ctx->lookup(id);
  auto size = mllvm->ctx->get_arr_size(id);
  auto condition = new RelExpr(index, RelOp::ge, new IntLiteral(size));
  auto debug_callout_args = new CalloutArgsList();
  auto debugstr = "Index out of bounds - Accessing `%d` of `" + id + "` of size `" + to_string(size) + "`\n";
  debug_callout_args->add(index);
  debug_callout_args->add(new StringLiteral(debugstr.c_str()));
  get_conditional_exit(condition, debug_callout_args)->codegen();
  auto _index = index->codegenf();
  vector<llvm::Value *> array_index;
  array_index.push_back(mllvm->Builder->getInt32(0));
  array_index.push_back(_index);
  return mllvm->Builder->CreateInBoundsGEP(_var, array_index, id + "_index");
}
