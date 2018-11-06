#include "base.hpp"

int get_lineno() {
 // default fallback
 return lineno;
}

Base::Base() {
  lno = lineno;
}

int Base::get_lineno() {
  return lno;
}
