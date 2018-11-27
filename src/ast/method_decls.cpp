#include "method_decls.hpp"

MethodDeclArg::MethodDeclArg(Type _type, const char *_id) {
  type = _type;
  id = string(_id);
}

int MethodDeclArg::print() {
  printText(typeToString(type) + ":" + id + ":MethodDeclArg");
  return pidcount;
}

void MethodDeclArgs::add(MethodDeclArg* arg) {
  args.push_front(arg);
}

int MethodDeclArgs::print() {
  printText("MethodDeclArgs");
  int p = pidcount;
  for (auto a: args) {
    int _a = a->print();
    printRelation(p, _a);
  }
  return p;
}

MethodDecl::MethodDecl(Type _type, const char *_id, MethodDeclArgs* _args, Block* _block) {
  isVoid = false;
  type = _type;
  id = string(_id);
  args = _args;
  block = _block;
}

MethodDecl::MethodDecl(const char *_id, MethodDeclArgs* _args, Block* _block) {
  isVoid = true;
  id = string(_id);
  args = _args;
  block = _block;
}

int MethodDecl::print() {
  int _a = args->print();
  int _b = block->print();
  string _t = isVoid ? "void" : typeToString(type);
  printText(_t + ":" + id + ":MethodDecl");
  printRelation(_a);
  printRelation(_b);
  return pidcount;
}

void MethodDecls::add(MethodDecl* method_decl) {
  list.push_front(method_decl);
}

int MethodDecls::print() {
  printText("MethodDecls");
  int p = pidcount;
  for (auto m: list) {
    int _m = m->print();
    printRelation(p, _m);
  }
  return p;
}

void MethodDeclArg::traverse() {
  CONTEXT_INSERT(id, CtxDataType(LocationType::var, id, type));
}

void MethodDeclArgs::traverse() {
  for (auto a: args) a->traverse();
}

vector<Type> MethodDeclArgs::get_types() {
  vector<Type> toret;
  for (auto a: args) toret.push_back(a->get_type());
  return toret;
}

void MethodDecl::traverse() {
  auto cdt = CtxDataType(LocationType::method, id, type);
  cdt.isVoid = isVoid;
  cdt.method_args = args->get_types();
  CONTEXT_INSERT(id, cdt);

  curMethodName = id;
  curMethodReturnVoid = isVoid;
  curMethodReturnType = type;

  context.newContext();
  args->traverse();
  block->traverse();
}

void MethodDecls::traverse() {
  for (auto m: list) m->traverse();
}

llvm::Value* MethodDeclArg::codegen() {
  return nullptr;
}

llvm::Value* MethodDeclArgs::codegen() {
  return nullptr;
}

llvm::Value* MethodDecl::codegen() {
  vector<llvm::Type *> param_types;
  for (auto a: args->args) param_types.push_back(llvmtype(a->get_type()));
  llvm::Type* ret_type = isVoid ? llvmtype() : llvmtype(type);

  auto FT = llvm::FunctionType::get(ret_type, param_types, false);
  auto F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, id, mllvm->TheModule);

  // Set names for all arguments.
  unsigned i = 0;
  for (auto &a : F->args()) a.setName(args->args[i++]->get_id());

  if (!F) return nullptr;
  mllvm->currentFn = F;

  // Create a new basic block to start insertion into.
  auto BB = mllvm->getBasicBlock("entry");
  mllvm->Builder->SetInsertPoint(BB);

  // Record the function arguments in the NamedValues map.
  mllvm->ctx->newContext();
  for (auto &a : F->args()) {
    mllvm->ctx->insert(a.getName(), &a);
  }

  block->codegen();
  if (!block->isReturn()) {
    if (isVoid) return mllvm->Builder->CreateRetVoid();
  //   else return mllvm->Builder->CreateRet(IntLiteral("0").codegen());
  }

  if (llvm::verifyFunction(*F))
    CODEGEN_ERROR("verifyFunction error in function \"" + id + "\" (check for missing returns)");

  mllvm->ctx->popContext();
  return F;
}

llvm::Value* MethodDecls::codegen() {
  llvm::Value* v;
  for (auto m: list) v = m->codegen();
  return v;
}
