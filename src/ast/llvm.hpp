#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRBuilder.h>

class MLLVM {
public:
  llvm::LLVMContext Context;
  llvm::Module *TheModule;
  llvm::IRBuilder<> *Builder;
  MLLVM() {};
};
