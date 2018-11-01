#include "base.hpp"

CtxDataType::CtxDataType () {
  not_found = true;
}

CtxDataType::CtxDataType (LocationType _lt, string _id, Type _type, int _arrsize) {
  lt = _lt;
  id = _id;
  type = _type;
  arrsize = _arrsize;
}
