#pragma once

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <iostream>
using namespace std;

enum class Type { _int, _boolean };

class Base {
public:
  virtual int print() = 0;
  virtual void traverse() = 0;
};

class Expr: public Base {
// Anything that can be evaluated
public:
  virtual int print() = 0;
  virtual void traverse() = 0;
  virtual Type get_type() = 0;
};

class Location: public Expr {
public:
  virtual int print() = 0;
  virtual void traverse() = 0;
};

class Statement: public Base {
// Anything that has context limited to itself
public:
  virtual int print() = 0;
  virtual void traverse() = 0;
};

string typeToString(Type type);

extern int pidcount;
int printText(int v);
int printText(char v);
int printText(const char *v);
int printText(string v);
void printRelation(int from, int to);
void printRelation(int to);

extern int lineno;
extern vector<pair<int, int> > errors;


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
