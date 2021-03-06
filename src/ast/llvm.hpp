#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include "base_minimal.hpp"

class MLLVMContext {
public:
  MLLVMContext() {};
  void newContext();
  void popContext();
  llvm::Value* lookup(string id);
  llvm::Value* insert(string id, Type type);
  llvm::Value* insert(string id, llvm::Value* val);
  llvm::Value* update(llvm::Value* var, llvm::Value* val);
  llvm::Value* update(llvm::AllocaInst* var, llvm::Value* val);
  llvm::Value* update(string id, llvm::Value* val);
  llvm::Value* load(llvm::Value* var);
  llvm::Value* load(llvm::AllocaInst* var);
  llvm::Value* load(string id);
  int update_arr_size(string arr, int size);
  int get_arr_size(string arr);
private:
  deque<map<string, llvm::Value*> > ctx;
  map<string, int> arr_size;
};

struct MLLVMLoopInfo {
  Location* loopvar;
  llvm::BasicBlock* conditionBB;
  llvm::BasicBlock* bodyBB;
  llvm::BasicBlock* afterBB;
};

class MLLVM {
public:
  llvm::LLVMContext Context;
  llvm::Module *TheModule;
  llvm::IRBuilder<> *Builder;
  llvm::Function* currentFn;
  MLLVM();
  MLLVMContext* ctx;
  stack<MLLVMLoopInfo> loops;
  llvm::AllocaInst* getAllocaInst(string id, Type type);
  llvm::BasicBlock* getBasicBlock(const char* desc);
};
