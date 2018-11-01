#include "base.hpp"

void Context::newContext() {
  ctx.push_front(map<string, CtxDataType> ());
}

void Context::popContext() {
  ctx.pop_front();
}

CtxDataType Context::lookup(string id) {
  for (auto m: ctx) {
    if (m.count(id)) return m[id];
  }
  errors.push_back(Error(2, id + " not found"));
  return CtxDataType();
}

bool Context::insert(string id, CtxDataType data) {
  if (ctx[0].count(id)) {
    errors.push_back(Error(1, "Duplicate " + id + " in same scope"));
    return false;
  }
  ctx[0][id] = data;
  return true;
}
