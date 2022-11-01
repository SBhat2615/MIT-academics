%{
	int vowels = 0;
	int consonants = 0;
%}

%%

[aeiouAEIOU]	{vowels++;};
.	            {consonants++;}

%%

int yywrap(){
	return 1;
}

int main(){
	yylex();
	printf("%d %d\n", vowels, consonants);
	return 0;
}