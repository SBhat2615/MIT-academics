%{
int chars = 0;
int words = 0;
int lines = 0;
int blanks = 0;
%}

%%

[a-zA-Z]+	{words++; chars += strlen(yytext);}
\n 			{chars++; lines++;}
[ ]			{blanks++;} 		
. 			{chars++;}

%%

int yywrap()
{
	return 1;
}

int main(int argc, char** argv)
{
	yylex();
	printf("Lines: %d Words: %d Characters: %d Blanks: %d\n", lines, words, chars, blanks);
	return 0;
}