%{
#include "parser.tab.h"
int lineno = 0;
%}

digit [0-9]
alpha [a-zA-Z_]
alphanum {alpha}|{digit}
char [ !#-&\(-\[\]-~]|\\\"|\\\'|\\\\|\\t|\\n
hex_digit {digit}|[a-fA-F]

%%
"callout" { return CALLOUT; }
"true"|"false" { return BOOL_LITERAL; }
\"{char}*\" { return STRING_LITERAL; }
\'{char}\' { return CHAR_LITERAL; }
{digit}+ { return INT_LITERAL; }
"0x"{hex_digit}+ { return INT_LITERAL; }
{alpha}{alphanum}*	{ return ID; }

"-"					{return '-';}
"!"					{return '!';}
"("					{return '(';}
")"					{return ')';}
"["					{return '[';}
"]"					{return ']';}
","					{return ',';}

"+"					{return '+';}
"*"					{return '*';}
"/"					{return '/';}
"%"					{return '%';}

"<"					{return LT;}
">"					{return GT;}
"<="					{return LE;}
">="					{return GE;}

"=="					{return EQ;}
"!="					{return NE;}

"&&"					{return AND;}
"||"					{return OR;}

[ \t]				{ }
\n		     		{++lineno;}
.					{ printf("Line No %d: Unrecognized Character\n", lineno); }

%%
