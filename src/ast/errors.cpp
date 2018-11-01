#include "errors.hpp"
#include <iostream>

Error::Error(int _eno, const char *_extra) {
  eno = _eno;
  extra = string(_extra);
  lno = lineno;
}

Error::Error(int _eno, string _extra) {
  eno = _eno;
  extra = _extra;
  lno = lineno;
}

void Error::print() {
  string e2 = extra != "" ? " - " + extra : "";
  cerr << "ERROR: " << eno << " at " << lno << e2 << endl;
}
