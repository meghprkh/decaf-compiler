#include "base.hpp"

void strReplaceAll(string& data, string search, string replace) {
  size_t pos = data.find(search);
  while(pos != string::npos) {
    data.replace(pos, search.size(), replace);
    pos = data.find(search, pos + replace.size());
  }
}

string escaped(const char *s) {
  string toret = string(s);
  strReplaceAll(toret, string("\\\""), string("\""));
  strReplaceAll(toret, string("\\\'"), string("\'"));
  strReplaceAll(toret, string("\\\\"), string("\\"));
  strReplaceAll(toret, string("\\t"), string("\t"));
  strReplaceAll(toret, string("\\n"), string("\n"));
  return toret;
}

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
  mllvm->currentFn = F;
  llvm::BasicBlock *BB = mllvm->getBasicBlock("entry");
  mllvm->Builder->SetInsertPoint(BB);
  if (Body->codegen()) {
    // Validate the generated code, checking for consistency.
    llvm::verifyFunction(*F);

    // F->print(llvm::errs());
    return F;
  }

  F->eraseFromParent();
  return nullptr;
}

// Return void
llvm::Type* llvmtype() {
  return llvm::Type::getVoidTy(mllvm->Context);
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
