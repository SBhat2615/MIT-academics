%{
  #include <stdio.h>
  #include <stdlib.h>
	int positive = 0;
	int negative = 0;
	int positive_floating = 0;
	int negative_floating = 0;
%}

%%

[+]?[1-9][0-9]*				{positive++;}
[-][1-9][0-9]*				{negative++;}
[+]?[0-9]*\.[0-9]*		{positive_floating++;}
[-][0-9]*\.[0-9]*		  {negative_floating++;} 
[ ] 
.                     {printf("Error !!\n"); exit(0);}

%%

int yywrap(){
	return 1;
}

int main(){
	yylex();
	printf("Positive: %d  Negative: %d  Positive floating: %d  Negative floating: %d\n", positive, negative, positive_floating, negative_floating);
	return 0;
}