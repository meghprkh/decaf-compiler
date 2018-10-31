#include "base.hpp"

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
