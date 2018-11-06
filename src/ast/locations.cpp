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
  auto cdt = CONTEXT_LOOKUP(id);
  if (cdt.lt != LocationType::var && !cdt.not_found) {
    ERROR(9, id + " is not a variable");
  }
  type = cdt.type;
}

void ArrLocation::traverse() {
  auto cdt = CONTEXT_LOOKUP(id);
  if (cdt.lt != LocationType::arr && !cdt.not_found) {
    ERROR(10, id + " is not an array");
  }
  type = cdt.type;
}
