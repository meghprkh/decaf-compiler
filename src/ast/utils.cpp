#include "base.hpp"

string typeToString(Type type) {
  switch (type) {
    case Type::_int : return string("int"); break;
    case Type::_boolean : return string("boolean"); break;
  }
  return string("undefinied_type");
}

int printText(int v) {
  printf("%d[%d]\n", ++pidcount, v);
  return pidcount;
}

int printText(char v) {
  printf("%d[%c]\n", ++pidcount, v);
  return pidcount;
}

int printText(const char* v) {
  printf("%d[%s]\n", ++pidcount, v);
  return pidcount;
}

int printText(string v) {
  printf("%d[%s]\n", ++pidcount, v.c_str());
  return pidcount;
}

void printRelation(int from, int to) {
  printf("%d-->%d\n", from, to);
}

void printRelation(int to) {
  printRelation(pidcount, to);
}

llvm::Value* wrap(Base *Body) {
  llvm::FunctionType *FT = llvm::FunctionType::get(llvm::Type::getInt32Ty(mllvm->Context), false);
  llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "main", mllvm->TheModule);
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(mllvm->Context, "entry", F);
  mllvm->Builder->SetInsertPoint(BB);
  if (llvm::Value *RetVal = Body->codegen()) {
    // Finish off the function.
    mllvm->Builder->CreateRet(RetVal);

    // Validate the generated code, checking for consistency.
    llvm::verifyFunction(*F);

    // F->print(llvm::errs());
    return F;
  }

  F->eraseFromParent();
  return nullptr;
}

llvm::Type* llvmtype(Type type) {
  return llvmtype(&type);
}

llvm::Type* llvmtype(Type* type) {
  switch(*type) {
    case Type::_int : return llvm::Type::getInt32Ty(mllvm->Context);
    case Type::_boolean : return llvm::Type::getInt1Ty(mllvm->Context);
  }
  return nullptr;
}

llvm::Value* CODEGEN_ERROR(string s) {
  return CODEGEN_ERROR(s.c_str());
}

llvm::Value* CODEGEN_ERROR(const char* s) {
  ERROR(-1, s);
  return nullptr;
}
