#include "literals.hpp"

IntLiteral::IntLiteral(const char *x) {
  value = atoi(x);
}

CharLiteral::CharLiteral(const char *x) {
  value = x[0];
}

BoolLiteral::BoolLiteral(const char *x) {
  value = x[0] == 't';
}

StringLiteral::StringLiteral(const char *x) {
  value = string(x);
}

void IntLiteral::print() {
  printf("%d", value);
}

void CharLiteral::print() {
  printf("\'%c\'", value);
}

void BoolLiteral::print() {
  printf("%s", value ? "true" : "false");
}

void StringLiteral::print() {
  cout << '\"' << value << '\"';
}
