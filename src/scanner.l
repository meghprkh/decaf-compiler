%{
#include "ast/all.hpp"
#include "parser.tab.hpp"
extern int lineno;
extern union Node yylval;
%}

digit [0-9]
alpha [a-zA-Z_]
alphanum {alpha}|{digit}
char [ !#-&\(-\[\]-~]|\\\"|\\\'|\\\\|\\t|\\n
hex_digit {digit}|[a-fA-F]

%%
"//"[^\n]* {++lineno;}

"boolean" { return BOOLEAN; }
"break" { return BREAK; }
"callout" { return CALLOUT; }
"class" { return CLASS; }
"continue" { return CONTINUE; }
"else" { return ELSE; }
"for" { return FOR; }
"if" { return IF; }
"int" { return INT; }
"return" { return RETURN; }
"void" { return VOID; }

"true"|"false" { yylval.token = strdup(yytext); return BOOL_LITERAL; }
\"{char}*\" { yylval.token = strdup(yytext); return STRING_LITERAL; }
\'{char}\' { yylval.token = strdup(yytext); return CHAR_LITERAL; }
{digit}+ { yylval.token = strdup(yytext); return INT_LITERAL; }
"0x"{hex_digit}+ { yylval.token = strdup(yytext); return INT_LITERAL; }
{alpha}{alphanum}*	{ yylval.token = strdup(yytext); return ID; }

"-"					{return '-';}
"!"					{return '!';}
"("					{return '(';}
")"					{return ')';}
"["					{return '[';}
"]"					{return ']';}
"{"					{return '{';}
"}"					{return '}';}
","					{return ',';}
";"					{return ';';}

"="					{return ASSIGN_EQ;}
"+="				{return ASSIGN_PE;}
"-="				{return ASSIGN_ME;}

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
