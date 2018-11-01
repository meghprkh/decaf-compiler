#include <string>
using namespace std;

extern int lineno;

class Error {
public:
  Error(int _eno, const char* _extra);
  Error(int _eno, string _extra = "");
  void print();
private:
  int eno, lno;
  string extra;
};
