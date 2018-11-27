#include "base.hpp"

MLLVM::MLLVM() {
  TheModule = new llvm::Module("decaff compiler", Context);
  Builder = new llvm::IRBuilder<> (Context);
  loops = stack<MLLVMLoopInfo>();
  ctx = new MLLVMContext();
}

llvm::AllocaInst* MLLVM::getAllocaInst(string id, Type type) {
  llvm::IRBuilder<> TmpB(&currentFn->getEntryBlock(), currentFn->getEntryBlock().begin());
  return TmpB.CreateAlloca(llvmtype(type), 0, id);
}

llvm::BasicBlock* MLLVM::getBasicBlock(const char *desc) {
  return llvm::BasicBlock::Create(this->Context, desc, this->currentFn);
}

void MLLVMContext::newContext() {
  ctx.push_front(map<string, llvm::Value*> ());
}

void MLLVMContext::popContext() {
  ctx.pop_front();
}

llvm::Value* MLLVMContext::lookup(string id) {
  for (auto m: ctx) {
    if (m.count(id)) return m[id];
  }
  auto v = mllvm->TheModule->getNamedGlobal(id);
  if (v) return v;
  CODEGEN_ERROR(id + " not found");
  return nullptr;
}

llvm::Value* MLLVMContext::insert(string id, llvm::Value* val) {
  if (ctx[0].count(id)) {
    CODEGEN_ERROR("Duplicate " + id + " in same scope");
    return nullptr;
  }
  ctx[0][id] = (llvm::Value*) val;
  return ctx[0][id];
}

llvm::Value* MLLVMContext::insert(string id, Type type) {
  if (ctx[0].count(id)) {
    CODEGEN_ERROR("Duplicate " + id + " in same scope");
    return nullptr;
  }
  ctx[0][id] = (llvm::Value*) mllvm->getAllocaInst(id, type);
  return ctx[0][id];
}

llvm::Value* MLLVMContext::update(llvm::Value* var, llvm::Value* val) {
  return mllvm->Builder->CreateStore(val, var);
}

llvm::Value* MLLVMContext::update(llvm::AllocaInst* var, llvm::Value* val) {
  return this->update((llvm::Value*) var, val);
}

llvm::Value* MLLVMContext::update(string id, llvm::Value* val) {
  return this->update(this->lookup(id), val);
}

llvm::Value* MLLVMContext::load(llvm::Value* var) {
  return mllvm->Builder->CreateLoad(var);
}

llvm::Value* MLLVMContext::load(llvm::AllocaInst* var) {
  return this->load((llvm::Value *) var);
}

llvm::Value* MLLVMContext::load(string id) {
  return this->load(this->lookup(id));
}
