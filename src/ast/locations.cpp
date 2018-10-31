#include "locations.hpp"

VarLocation::VarLocation(const char *_id) {
  id = string(_id);
}

ArrLocation::ArrLocation(const char *_id, Expr *_index) {
  id = string(_id);
  index = _index;
}

int VarLocation::print() {
  printText(id);
  return pidcount;
}

int ArrLocation::print() {
  int _index = index->print();
  printText(id + ":arr");
  printRelation(_index);
  return pidcount;
}
