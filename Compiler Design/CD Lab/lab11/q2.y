%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror();
%}

%token DATATYPE ID SEMICOLON NL COMMA if else OCBRAC CCBRAC OFBRAC CFBRAC



%%
stmt: DC SEMICOLON | DS NL 		{printf("Valid Expression\n"); exit(0);}
	;
DC : DATATYPE idlist SEMICOLON
|
;
DS : if OCBRAC stmt CCBRAC OFBRAC stmt CFBRAC
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