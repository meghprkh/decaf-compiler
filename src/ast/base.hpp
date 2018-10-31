#pragma once

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

enum class Type { _int, _boolean };

class Base {
public:
  virtual int print() = 0;
};

class Expr: public Base {
// Anything that can be evaluated
public:
  virtual int print() = 0;
  virtual Type get_type() = 0;
};

class Location: public Expr {
public:
  virtual int print() = 0;
};

class Statement: public Base {
// Anything that has context limited to itself
public:
  virtual int print() = 0;
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
