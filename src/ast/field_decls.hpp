#include "base.hpp"

class FieldDeclArgs: public Base {
public:
  FieldDeclArgs() {};
  void add(const char* _id);
  void add(const char* _id, const char* index);
  int print();
  void traverse();
  void traverse(Type type);
private:
  deque<string> vars;
  deque<pair<string, int> > arrs;
};

class FieldDecl: public Base {
public:
  FieldDecl(Type _type, FieldDeclArgs* _args);
  int print();
  void traverse();
private:
  Type type;
  FieldDeclArgs* args;
};

class FieldDecls: public Base {
public:
  FieldDecls() {};
  void add(FieldDecl* _f);
  int print();
  void traverse();
private:
  deque<FieldDecl*> list;
};
