#include "base.hpp"

MLLVM::MLLVM() {
  TheModule = new llvm::Module("decaff compiler", Context);
  Builder = new llvm::IRBuilder<> (Context);
}
