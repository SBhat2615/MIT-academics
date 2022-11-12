%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror();
%}

%token DATATYPE ID SEMICOLON NL COMMA

%%
stmt:declaration NL 		{printf("Valid Expression\n"); exit(0);}
	;
declaration: DATATYPE idlist SEMICOLON
|
;
idlist: ID
	|ID COMMA idlist
	;
%%

int yyerror(char *msg)
{
	printf("Invalid Declaration\n");
	exit(0);
}

void main ()
{
	printf("Enter the declaration statement: \n");
	yyparse();
}