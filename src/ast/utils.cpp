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

void printRelation(int from, int to) {
  printf("%d-->%d\n", from, to);
}

void printRelation(int to) {
  printRelation(pidcount, to);
}
