#pragma once

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <stack>
#include <iostream>
#include <llvm/IR/Value.h>
using namespace std;


enum class Type { _int, _boolean };


class Base {
public:
  Base();
  virtual int print() = 0;
  virtual void traverse() = 0;
  virtual llvm::Value* codegen() = 0;
  int get_lineno();
private:
  int lno;
};

class Expr: public Base {
// Anything that can be evaluated
public:
  virtual int print() = 0;
  virtual void traverse() = 0;
  virtual Type get_type() = 0;
  virtual llvm::Value* codegen() = 0;
  llvm::Value* codegenf();
};

class Location: public Expr {
public:
  virtual int print() = 0;
  virtual void traverse() = 0;
  virtual string get_id() = 0;
  virtual llvm::Value* codegen() = 0;
};

class Statement: public Base {
// Anything that has context limited to itself
public:
  virtual int print() = 0;
  virtual void traverse() = 0;
  virtual llvm::Value* codegen() = 0;
  virtual bool isReturn() = 0;
};

string typeToString(Type type);
