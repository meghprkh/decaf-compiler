#pragma once

#include "errors.hpp"
#include "base_minimal.hpp"
#include "llvm.hpp"

int get_lineno(); // default fallback which uses global lineno (inaccurate)

// This uses the class's get_lineno if inherited from Base (basically not
// Context) else the global fallback
#define ERROR(eno, desc) errors.push_back(Error(eno, get_lineno(), desc))
// Set the gllobal lineno in case of context lookup and insert, which is then used
// for outputting correct lineno in error
#define CONTEXT_LOOKUP(x) (lineno = get_lineno()) ? context.lookup(x) : CtxDataType()
#define CONTEXT_INSERT(x, y) (lineno = get_lineno()) ? context.insert(x, y) : false

string escaped(const char* s);

extern FILE* mermaidPrint;
extern int pidcount;
int printText(int v);
int printText(char v);
int printText(const char *v);
int printText(string v);
void printRelation(int from, int to);
void printRelation(int to);

extern int lineno;
extern vector<Error> errors;


enum class LocationType { var, arr, method };

class CtxDataType {
public:
  CtxDataType ();
  CtxDataType (LocationType _lt, string _id, Type _type = Type::_int, int _arrsize = -1);

  bool not_found = false;

  LocationType lt;
  string id;
  Type type;
  bool isVoid = false;
  int arrsize = -1;

  // push_back to this
  vector<Type> method_args;
};

class Context {
public:
  Context() {};
  void newContext();
  void popContext();
  CtxDataType lookup(string id);
  // false if already exists (error)
  bool insert(string id, CtxDataType data);
private:
  deque<map<string, CtxDataType> > ctx;
};


extern Context context;
extern MLLVM* mllvm;

llvm::Value* wrap(Base* body);
llvm::Type* llvmtype(); // Returns void type
llvm::Type* llvmtype(Type type);
llvm::Type* llvmtype(Type* type);

llvm::Value* CODEGEN_ERROR(string s);
llvm::Value* CODEGEN_ERROR(const char* s);
