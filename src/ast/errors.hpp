#include <string>
using namespace std;

extern int lineno;

class Error {
public:
  Error(int _eno, int lineno, const char* _extra);
  Error(int _eno, int lineno, string _extra = "");
  void print();
private:
  int eno, lno;
  string extra;
};
