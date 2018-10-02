%{
#include <stdio.h>
#define YYDEBUG 1
%}

%token BOOLEAN BREAK CALLOUT CLASS CONTINUE ELSE FOR IF INT RETURN VOID
%token ID
%token STRING_LITERAL INT_LITERAL CHAR_LITERAL BOOL_LITERAL
%token ASSIGN_EQ ASSIGN_PE ASSIGN_ME
%token LT GT LE GE
%token EQ NE
%token AND OR
%left '+' '-'
%left '*' '/'

%%

program
	: CLASS ID '{' field_decls method_decls '}'
	;

field_decls
	: field_decls field_decl
	| %empty
	;

field_decl
	: type field_decl_args ';'
	;

field_decl_args
	: ID ',' field_decl_args
	| ID '[' INT_LITERAL ']' ',' field_decl_args
	| ID
	| ID '[' INT_LITERAL ']'
	;

method_decls
	: method_decl method_decls
	| %empty
	;

method_decl
	: type ID '(' method_decl_args ')' block
	| VOID ID '(' method_decl_args ')' block
	;

method_decl_args
	: method_decl_arg ',' method_decl_args
	| method_decl_arg
	| %empty
	;

method_decl_arg
	: type ID
	;

block
	: '{' var_decls statements '}'
	;

var_decls
	: var_decl var_decls
	| %empty
	;

var_decl
	: type var_decl_vars ';'
	;

var_decl_vars
	: ID ',' var_decl_vars
	| ID
	;

statements
	: statement statements
	| %empty
	;

type: INT | BOOLEAN ;

statement
	: location assign_op expr ';'
	| method_call ';'
	| IF '(' expr ')' block ELSE block
	| IF '(' expr ')' block
	| FOR ID ASSIGN_EQ expr ',' expr block
	| RETURN expr ';'
	| RETURN ';'
	| BREAK ';'
	| CONTINUE ';'
	| block
	;

assign_op
	: ASSIGN_EQ
	| ASSIGN_PE
	| ASSIGN_ME
	;

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
	| %empty
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
