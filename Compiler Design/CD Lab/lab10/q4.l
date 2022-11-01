%{
    int pcount=0,scount=0;
%}

%%
printf {pcount++; fprintf(yyout,"WRITE");}
scanf {scount++; fprintf(yyout,"READ");}

%%

int yywrap(){
  return 1;
}

int main()
{
    yyin=fopen("input.c","r");
    yyout=fopen("output.c","w");
    yylex();
    printf("Number of printf : %d\n",pcount);
    printf("Number of scanf : %d\n",scount);
}