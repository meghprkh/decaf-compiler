#include "base.hpp"

void printText(int v) {
  printf("%d[%d]\n", ++pidcount, v);
}

void printText(char v) {
  printf("%d[%c]\n", ++pidcount, v);
}

void printText(const char* v) {
  printf("%d[%s]\n", ++pidcount, v);
}

void printText(string v) {
  printf("%d[%s]\n", ++pidcount, v.c_str());
}
