%{
	#include <stdio.h>
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*  printf("Valid Identifier");

%%

int yywrap(){
	return 1;
}

int main(int argc, char** argv){
	yylex();
	char stat[20];
	printf("Enter a valid C statement:");
	scanf("%s", stat);
}

