%{
#include "q1.tab.h"
%}

%%
\n 						{return NL; }
int 					{return DATATYPE;}
float 				{return DATATYPE;}
double 				{return DATATYPE;}
char 					{return DATATYPE;}
[a-zA-Z][a-zA-Z0-9_]* 	{return ID; }
","						{return COMMA; }
";"						{return SEMICOLON; }
%%

int yywrap(){
	return 1;
}