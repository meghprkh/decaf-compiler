#include "literals.hpp"

IntLiteral::IntLiteral(const char *x) {
  value = (int) strtol(x, NULL, 0);
}

CharLiteral::CharLiteral(const char *x) {
  value = escaped(x)[0];
}

BoolLiteral::BoolLiteral(const char *x) {
  value = x[0] == 't';
}

StringLiteral::StringLiteral(const char *x) {
  value = escaped(x);
}

int IntLiteral::print() {
  printText(value);
  return pidcount;
}

int CharLiteral::print() {
  printText(value);
  return pidcount;
}

int BoolLiteral::print() {
  printText(value ? "true" : "false");
  return pidcount;
}

int StringLiteral::print() {
  printText(value);
  return pidcount;
}

Type IntLiteral::get_type() {
  return Type::_int;
}

Type CharLiteral::get_type() {
  return Type::_int;
}

Type BoolLiteral::get_type() {
  return Type::_boolean;
}

Type StringLiteral::get_type() {
  return Type::_int;
}

llvm::Value* IntLiteral::codegen() {
  return llvm::ConstantInt::get(mllvm->Context, llvm::APInt(32, static_cast<uint64_t>(value), true));
}

llvm::Value* CharLiteral::codegen() {
  return llvm::ConstantInt::get(mllvm->Context, llvm::APInt(8, static_cast<uint64_t>(value)));
}

llvm::Value* BoolLiteral::codegen() {
  return llvm::ConstantInt::get(mllvm->Context, llvm::APInt(1, value));
}

llvm::Value* StringLiteral::codegen() {
  return mllvm->Builder->CreateGlobalStringPtr(value);
}
