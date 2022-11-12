#include<stdio.h>
#include "getnexttoken.h"
token tok;
FILE * f;
void program();
void declarations();
void data_types();
void identifier_list();
void A();
void assign_stat();
void statement_list();
void statement();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();
void dPrime();
void decision_stat();
void looping_stat();
void statement_list();
void program()
{
	if (strcmp(tok.token, "main") == 0)
	{
		tok = getnexttoken(f);
		if (strcmp(tok.token, "(") == 0)
		{
			tok = getnexttoken(f);
			if (strcmp(tok.token, ")") == 0)
			{
				tok = getnexttoken(f);
				if (strcmp(tok.token, "{") == 0)
				{
					tok = getnexttoken(f);
					declarations();
					statement_list();
					if (strcmp(tok.token, "}") == 0)
					{
						return;
					}
					else
					{
						printf("} missing at row=%d col=%d\n", tok.row, tok.col);
						exit(1);
					}
				}
				else
				{
					printf("{ missing at row=%d col=%d\n", tok.row, tok.col);
					exit(1);
				}
			}
			else
			{
				printf(") missing at row=%d col=%d\n", tok.row, tok.col);
				exit(1);
			}
		}
		else
		{
			printf("( missing at row=%d col=%d\n", tok.row, tok.col);
			exit(1);
		}
	}
	else
		{
			printf("\"main\" missing at row=%d col=%d\n", tok.row, tok.col);
			exit(1);
		}
}
void declarations(){
if((strcmp(tok.tokenname,"id")==0)||(strcmp(tok.token,"if")==0)||(strcmp(tok.token,"while")==0)||(strcmp(tok.token,"for")==0)||(strcmp(tok.token,"}")==0)){
return;
}
else if((strcmp(tok.token,"int")==0)||(strcmp(tok.token,"char")==0)){
data_types();
identifier_list();
if(strcmp(tok.token,";")==0){
tok=getnexttoken(f);
declarations();
}
else {
printf("Expected ; at row: %d col:%d",tok.row,tok.col);
exit(0);
}
}
else{
printf("expected datatype or identifier at row: %d col: %d",tok.row,tok.col);
exit(1);}
}

void data_types()
{
	if (strcmp(tok.token, "int") == 0)
	{
		tok = getnexttoken(f);
		return;
	}
	else if (strcmp(tok.token, "char") == 0)
	{
		tok = getnexttoken(f);
		return;
	}
	else
	{
		printf("expected datatype at row=%d col=%d\n", tok.row, tok.col);
		exit(1);
	}
}
void identifier_list()
{
	if (strcmp(tok.tokenname, "id") == 0)
	{
		tok = getnexttoken(f);
		A();
	}
	else{
		printf("Missing id at row=%d col=%d\n", tok.row, tok.col);
		exit(0);
		}
}
void A()
{
	if (strcmp(tok.token, ",") == 0)
	{
		tok = getnexttoken(f);
		identifier_list();
	}
	else if (strcmp(tok.token, "[") == 0)
	{
		tok = getnexttoken(f);
		if (strcmp(tok.tokenname, "num") == 0)
		{
			tok = getnexttoken(f);
			if (strcmp(tok.token, "]") == 0)
			{
				tok = getnexttoken(f);
				if (strcmp(tok.token, ",") == 0)
				{
					tok = getnexttoken(f);
					identifier_list();
				}
				else
					return;
			}
			else
	{
	printf("Expected ] at row:%d col:%d",tok.row, tok.col);
	exit(0);
	}
		}
		else
	{
	printf("Expected num at row:%d col:%d",tok.row, tok.col);
	exit(0);
	}
	}
}
void statement_list()
{
	if (strcmp(tok.token, "}") == 0)
		return;
	else if(strcmp(tok.tokenname, "id") == 0||strcmp(tok.token, "if") == 0||strcmp(tok.token, "while") == 0||strcmp(tok.token, "for") == 0){
	statement();
	statement_list();
	}
	else
	{
	printf("Expected id or } at row:%d col:%d",tok.row, tok.col);
	exit(0);
	}
}
void statement()
{
if(strcmp(tok.tokenname, "id")==0){
	assign_stat();
	if (strcmp(tok.token, ";") == 0)
	{
		tok = getnexttoken(f);
		return;
	}
	else
	{
	printf("Expected ; at row:%d col:%d",tok.row, tok.col);
	exit(0);
	}
	}
else if(strcmp(tok.token, "if")==0){
decision_stat();
}
else if(strcmp(tok.token, "for")==0||strcmp(tok.token, "while")==0){
looping_stat();
}
else{
printf("Expected statements at row:%d col:%d",tok.row, tok.col);
exit(0);
}
	
}
void assign_stat()
{
	if (strcmp(tok.tokenname, "id") == 0)
	{
		tok = getnexttoken(f);
		if (strcmp(tok.token, "=") == 0)
		{
			tok = getnexttoken(f);
			expn();
		}
		else
		{
			printf("= missing at row=%d col=%d\n", tok.row, tok.col);
			exit(1);
		}
	}
	else
	{
		printf("Expected id at row=%d col=%d\n", tok.row, tok.col);
		exit(1);
	}
}
void expn()
{
	simple_expn();
	eprime();
}
void eprime()
{
if(strcmp(tok.token, ";") == 0||(strcmp(tok.token, ")") == 0)){
return;
}
else if((strcmp(tok.token, "==") == 0)||(strcmp(tok.token, "!=") == 0)||(strcmp(tok.token, "<=") == 0)||(strcmp(tok.token, ">=") == 0)||(strcmp(tok.token, ">") == 0)||(strcmp(tok.token, "<") == 0)){
	relop();
	simple_expn();
	}
	else
	{
	printf("Expected relop at row:%d col:%d",tok.row, tok.col);
	exit(1);
	}
}
void simple_expn()
{
	term();
	seprime();
}
void seprime()
{
	if ((strcmp(tok.token, ";") == 0)||(strcmp(tok.token, "==") == 0)||(strcmp(tok.token, "!=") == 0)||(strcmp(tok.token, "<=") == 0)||(strcmp(tok.token, ">=") == 0)||(strcmp(tok.token, ">") == 0)||(strcmp(tok.token, "<") == 0)||(strcmp(tok.token, ")") == 0))
	    return;
	else if(strcmp(tok.token, "+") == 0||strcmp(tok.token, "-") == 0){
	addop();
	term();
	seprime();
	}
	else
	{
	printf("Expected addop or ; at row:%d col:%d",tok.row, tok.col);
	exit(1);
	}
}
void term()
{
	factor();
	tprime();
}
void tprime()
{

if (strcmp(tok.token, ";") == 0||strcmp(tok.token, "==") == 0||strcmp(tok.token, "!=") == 0||strcmp(tok.token, "<=") == 0||strcmp(tok.token, ">=") == 0||strcmp(tok.token, ">") == 0||strcmp(tok.token, "<") == 0||strcmp(tok.token, "+") == 0||strcmp(tok.token, "-") == 0||(strcmp(tok.token, ")") == 0))
	    return;
	else if((strcmp(tok.token, "*") == 0)||(strcmp(tok.token, "/") == 0)||(strcmp(tok.token, "%") == 0)){
	
	mulop();
	
	factor();
	
	tprime();
	
	}
	else
	{
	printf("Expected mulop or relop or addop or ; at row:%d col:%d",tok.row, tok.col);
	exit(1);
	}
	
}
void factor()
{
	if (strcmp(tok.tokenname, "id") == 0)
	{
		tok = getnexttoken(f);
		return;
	}
	else if (strcmp(tok.tokenname, "num") == 0)
	{
		tok = getnexttoken(f);
		return;
	}
	else
	{
	printf("Expected id or num at row:%d col:%d",tok.row, tok.col);
	exit(1);
	}
}
void relop()
{

	if (strcmp(tok.token, "!=") == 0)
	{
		tok = getnexttoken(f);
	return;
	}
	if (strcmp(tok.token, "<=") == 0)
	{
		tok = getnexttoken(f);
		return;
	}
	if (strcmp(tok.token, ">=") == 0)
	{
		tok = getnexttoken(f);
		return;
	}	
	if (strcmp(tok.token, "<") == 0)
	{
		tok = getnexttoken(f);
		return;
		}
	if(strcmp(tok.token, "==") == 0)
	{
		tok = getnexttoken(f);
		return;
	}
	if (strcmp(tok.token, ">") == 0)
	{
		tok = getnexttoken(f);
		return;
	}
	else
	{
	printf("Expected relop at row:%d col:%d",tok.row, tok.col);
	exit(0);
	}
}
void addop()
{
	if (strcmp(tok.token, "+") == 0)
	{
		tok = getnexttoken(f);
		return;
	}
	else if (strcmp(tok.token, "-") == 0)
	{
		tok = getnexttoken(f);
		return;
	}
	else
	{
	printf("Expected + or - at row:%d col:%d",tok.row, tok.col);
	exit(1);
	}
}
void mulop()
{
	if (strcmp(tok.token, "*") == 0)
	{
		tok = getnexttoken(f);
		return;
	}
	else if (strcmp(tok.token, "/") == 0)
	{
		tok = getnexttoken(f);
		return;
	}
	else if (strcmp(tok.token, "%") == 0)
	{
		tok = getnexttoken(f);
		return;
	}
	else
	{
	printf("Expected mulop at row:%d col:%d",tok.row, tok.col);
	exit(1);
	}
}
void decision_stat()
{
    if (strcmp(tok.token, "if") == 0)
    {
        tok = getnexttoken(f);
        if (strcmp(tok.token, "(") == 0)
        {
            tok = getnexttoken(f);
            expn();
            if (strcmp(tok.token, ")") == 0)
            {
                tok = getnexttoken(f);
                if (strcmp(tok.token, "{") == 0)
                {
                    tok = getnexttoken(f);
                    statement_list();
                    if (strcmp(tok.token, "}") == 0)
                    {
                        tok = getnexttoken(f);
                        dPrime();
                        return;
                    }
                    else
                    {
                        printf("ERROR: missing \"}\" at row=%d col=%d\n", tok.row, tok.col);
                        exit(1);
                    }
                }
                else
                {
                    printf("ERROR: missing \"{\" at row=%d col=%d\n", tok.row, tok.col);
                    exit(1);
                }
            }
            else
            {
                printf("ERROR: missing \")\" at row=%d col=%d\n", tok.row, tok.col);
                exit(1);
            }
        }
        else
        {
            printf("ERROR: missing \"(\" at row=%d col=%d\n", tok.row, tok.col);
            exit(1);
        }
    }
    else
    {
        printf("ERROR: missing \"keyword\" at row=%d col=%d\n", tok.row, tok.col);
        exit(1);
    }
}
void dPrime()
{
if((strcmp(tok.tokenname,"id")==0)||(strcmp(tok.token,"if")==0)||(strcmp(tok.token,"while")==0)||(strcmp(tok.token,"for")==0)||(strcmp(tok.token,"}")==0))
return;
    if (strcmp(tok.token, "else") == 0)
    {
        tok = getnexttoken(f);
        if (strcmp(tok.token, "{") == 0)
        {
            tok = getnexttoken(f);
            statement_list();
            if (strcmp(tok.token, "}") == 0)
            {
                tok = getnexttoken(f);
                return;
            }
            else
            {
                printf("ERROR: missing \"}\" at row=%d col=%d\n", tok.row, tok.col);
                exit(1);
            }
        }
        else
        {
            printf("ERROR: missing \"{\" at row=%d col=%d\n", tok.row, tok.col);
            exit(1);
        }
    }
    else{
            printf("Expected else or id at row=%d col=%d\n", tok.row, tok.col);
            exit(1);
        }
        
}
void looping_stat()
{
    if (strcmp(tok.token, "while") == 0)
    {
        tok = getnexttoken(f);
        if (strcmp(tok.token, "(") == 0)
        {
            tok = getnexttoken(f);
            expn();
            if (strcmp(tok.token, ")") == 0)
            {
                tok = getnexttoken(f);
                if (strcmp(tok.token, "{") == 0)
                {
                    tok = getnexttoken(f);
                    statement_list();
                    if (strcmp(tok.token, "}") == 0)
                    {
                        tok = getnexttoken(f);
                        return;
                    }
                    else
                    {
                        printf("ERROR: missing \"}\" at row=%d col=%d\n", tok.row, tok.col);
                        exit(1);
                    }
                }
                else
                {
                    printf("ERROR: missing \"{\" at row=%d col=%d\n", tok.row, tok.col);
                    exit(1);
                }
            }
            else
            {
                printf("ERROR: missing \")\" at row=%d col=%d\n", tok.row, tok.col);
                exit(1);
            }
        }
        else
        {
            printf("ERROR: missing \"(\" at row=%d col=%d\n", tok.row, tok.col);
            exit(1);
        }
    }
    
    else if (strcmp(tok.token, "for") == 0)
    {
        tok = getnexttoken(f);
        if (strcmp(tok.token, "(") == 0)
        {
            tok = getnexttoken(f);
            assign_stat();
            if (strcmp(tok.token, ";") == 0)
            {
                tok = getnexttoken(f);
                expn();
                if (strcmp(tok.token, ";") == 0)
                {
                    tok = getnexttoken(f);
                    assign_stat();
                    if (strcmp(tok.token, ")") == 0)
                    {
                        tok = getnexttoken(f);
                        if (strcmp(tok.token, "{") == 0)
                        {
                            tok = getnexttoken(f);
                            statement_list();
                            if (strcmp(tok.token, "}") == 0)
                            {
                                tok = getnexttoken(f);
                                return;
                            }
                            else
                            {
                                printf("ERROR: missing \"}\" at row=%d col=%d\n", tok.row, tok.col);
                                exit(1);
                            }
                        }
                        else
                        {
                            printf("ERROR: missing \"{\" at row=%d col=%d\n", tok.row, tok.col);
                            exit(1);
                        }
                    }
                    else
                    {
                        printf("ERROR: missing \")\" at row=%d col=%d\n", tok.row, tok.col);
                        exit(1);
                    }
                }
                else
                {
                    printf("ERROR: missing \";\" at row=%d col=%d\n", tok.row, tok.col);
                    exit(1);
                }
            }
            else
            {
                printf("ERROR: missing \";\" at row=%d col=%d\n", tok.row, tok.col);
                exit(1);
            }
        }
        else
        {
            printf("ERROR: missing \"(\" at row=%d col=%d\n", tok.row, tok.col);
            exit(1);
        }
    }
    else
    {
        printf("ERROR: missing \"keyword\" at row=%d col=%d\n", tok.row, tok.col);
        exit(1);
    }
}


int main(){
f=fopen("input.c","r");
tok=getnexttoken(f);
program();
printf("compiled successfully");
return 0;
}