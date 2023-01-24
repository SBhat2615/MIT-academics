%{
  #include <stdio.h>
  #include <stdlib.h>
  int vowels = 0, consonants = 0;
%}

%%
[aeiouAEIOU]  {vowels++;}
\n            {}
[^aeiouAEIOU] {consonants++;}

%%
int yywrap(){
  return 1;
}

int main(){
  yylex();
  printf("Vowels: %d\nConsonants: %d\n", vowels, consonants);
  return 0;
}