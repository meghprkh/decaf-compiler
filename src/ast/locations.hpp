#include "base.hpp"

class VarLocation: public Location {
public:
  VarLocation(const char *_id);
  int print();
  Type get_type() { return type; }
  void traverse();
private:
  string id;
  Type type;
};

class ArrLocation: public Location {
public:
  ArrLocation(const char *_id, Expr *_index);
  int print();
  Type get_type() { return type; }
  void traverse();
private:
  string id;
  Expr* index;
  Type type;
};
