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

void VarLocation::traverse() {
  auto cdt = context.lookup(id);
  if (cdt.lt != LocationType::var) {
    errors.push_back(make_pair(9, lineno));
  }
  type = cdt.type;
}

void ArrLocation::traverse() {
  auto cdt = context.lookup(id);
  if (cdt.lt != LocationType::arr) {
    errors.push_back(make_pair(10, lineno));
  }
  type = cdt.type;
}
