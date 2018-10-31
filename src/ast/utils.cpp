#include "base.hpp"

string typeToString(Type type) {
  switch (type) {
    case Type::_int : return string("int"); break;
    case Type::_boolean : return string("boolean"); break;
  }
}

int printText(int v) {
  printf("%d[%d]\n", ++pidcount, v);
  return pidcount;
}

int printText(char v) {
  printf("%d[%c]\n", ++pidcount, v);
  return pidcount;
}

int printText(const char* v) {
  printf("%d[%s]\n", ++pidcount, v);
  return pidcount;
}

int printText(string v) {
  printf("%d[%s]\n", ++pidcount, v.c_str());
  return pidcount;
}

void printRelation(int from, int to) {
  printf("%d-->%d\n", from, to);
}

void printRelation(int to) {
  printRelation(pidcount, to);
}
