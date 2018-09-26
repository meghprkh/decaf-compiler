%{
#include <stdio.h>
#define YYDEBUG 1
%}

%token ID
%token CALLOUT
%token STRING_LITERAL INT_LITERAL CHAR_LITERAL BOOL_LITERAL
%token LT GT LE GE
%token EQ NE
%token AND OR
%left '+' '-'
%left '*' '/'

%%

expr
	: location
	| method_call
	| literal
	| expr bin_op expr
	| '-' expr
	| '!' expr
	| '(' expr ')'
	;

location
	: ID
	| ID '[' expr ']'
	;

method_call
	: method_name '(' method_args ')'
	| CALLOUT '(' STRING_LITERAL ')'
	| CALLOUT '(' STRING_LITERAL ',' callout_args ')'
	;

method_name: ID;

method_args
	: expr ',' method_args
	| expr
	;

callout_args
	: STRING_LITERAL ',' callout_args
	| expr ',' callout_args
	| STRING_LITERAL
	| expr
	;

literal
	: INT_LITERAL
	| CHAR_LITERAL
	| BOOL_LITERAL
	;

bin_op
	: arith_op
	| rel_op
	| eq_op
	| cond_op
	;

arith_op: '+' | '-' | '*' | '/' | '%';
rel_op: LT | GT | LE | GE;
eq_op: EQ | NE;
cond_op: AND | OR;

%%

extern int yydebug;
main(int argc, char **argv)
{
	yydebug = 1;
	yyparse();
	printf("Parsing Over\n");
}

yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}
