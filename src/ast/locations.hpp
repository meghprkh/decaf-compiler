#include "base.hpp"

class Location: public Expr {
public:
  virtual int print() = 0;
};

class VarLocation: public Location {
public:
  VarLocation(const char *_id);
  int print();
private:
  string id;
};

class ArrLocation: public Location {
public:
  ArrLocation(const char *_id, Expr *_index);
  int print();
private:
  string id;
  Expr* index;
};
