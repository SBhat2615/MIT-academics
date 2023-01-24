#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Token {
	char name[128];
	char type[128];
}Token;

Token* T;

typedef struct ST {
	char name[128];
}ST;

ST Table[100];
int idx;

FILE* input;
int fp;
int size;

Token* createToken(char* l, char* t) {
	Token* T = malloc(sizeof(Token));
	strcpy(T->name, l);
	strcpy(T->type, t);
	return T;
}

void printToken(Token *T) {
	printf("<%s, %s>\n", T->name,T->type);
}

int isExisting(char* name) {
	for(int i = 0; i < idx; i++) 
		if(!strcmp(Table[i].name, name))
			return 1;
	return 0;
}

Token* getNextNumber() { 
	fseek(input, fp, 0);
	char word[128]; int i = 0;
	char ch;

	while ( isdigit(ch = fgetc(input) )) word[i++] = ch;
	word[i] = '\0';
	if (i>0) 
		return createToken(word, "NUM");
	//printf("returning null\n");
	return NULL;
}


Token* getNextKeyword() { 
	fseek(input, fp, 0);
	char word[128]; int i = 0;
	char ch;

	while ( isalpha(ch =  fgetc(input)) ) word[i++] = ch;
	word[i] = '\0';

	if(!strcmp(word, "void"))
		return createToken("void", "KW");
	
	if(!strcmp(word, "int")){
		return createToken("int", "KW");
	}
	//printf("returning null\n");
	return NULL;
}

Token* getNextID() { 
	fseek(input, fp, 0);
	char word[128]; int i = 0;
	char ch;

	while ( isalnum(ch =  fgetc(input)) ) word[i++] = ch;
	word[i] = '\0';
	
	if(i > 0) {
		if(!isExisting(word))
			strcpy(Table[idx++].name, word);
		return createToken(word, "ID");
	}
	//printf("returning null\n");
	return NULL;
}

Token* getNextSpsym() {

	fseek(input, fp, 0);	
	char ch[2];
	ch[0] = fgetc(input);
	ch[1] = '\0';
	char spsym[] = {'{', '}','[',']', '(', ')', ';', '=', ','};
	for(int i = 0; i < 9; i++)
		if(ch[0] == spsym[i])
			return createToken(ch, "SP");
	//printf("returning null\n");
	return NULL;
}


Token* genNextToken() {
	Token* T;
  T = getNextNumber();
	if(T) return T;
	T = getNextSpsym();
	if(T) return T;
	T = getNextKeyword();
	if(T) return T;
	T = getNextID();
	if(T) return T;
	return NULL;
}


Token* getNextToken() {
	if(fp >= size)
		return NULL;
	Token *T;
	while ( (T = genNextToken()) == NULL)  {fp += 1;}
	//printToken(T);
	return T;
}

void displayST() {
	printf("\nDisplaying Symbol Table\n");
	for(int i = 0 ; i < idx; i++) 
		printf("<%s>\n", Table[i].name);
}


void error(char* msg) {
	printf("Error reading token %s. Expected %s\n", T->name, msg);
	exit(0);
}

int checkName(char* name) {
	return !strcmp(T->name, name);
}

int checkType(char* type) {
	return !strcmp(T->type, type);
}

void inc(){
	fp += strlen(T->name);
}


void func_decl();
void params();
void param_list();
void pl_prime();
void par();
void comp_stmt();
void stmt();
void local_decl();

void func_decl() {

	T = getNextToken();
	if(!checkName("int")) error("int");
	inc();

	T = getNextToken();
	if(!checkType("ID")) error("ID");
	inc();

	T = getNextToken();
	if(!checkName("(")) error("(");
	inc();

	params();

	T = getNextToken();
	if(!checkName(")")) error(")");
	inc();

	comp_stmt();

}


void params() {

	T = getNextToken();
	if(checkName("void")) {
		inc();
		return;
	}
	param_list();
}

void param_list() {
	par();
	pl_prime();
}

void pl_prime() {
	T = getNextToken();
	if(checkName(",")) {
		inc();
		par();
		pl_prime();
	}
}


void par() {

	T = getNextToken();
	if(!checkName("int")) error("int");
	inc();


	T = getNextToken();
	if(!checkType("ID")) error("ID");
	inc();


	T = getNextToken();
	if(checkName("[")) {
		inc();
		T = getNextToken();
		if(!checkName("]")) error("]");
		inc();
	}

}

void comp_stmt() {

	T = getNextToken();
	if(!checkName("{")) error("{");
	inc();

	local_decl();
	stmt();

	T = getNextToken();
	if(!checkName("}")) error("}");
	inc();

}

void local_decl() {

	T = getNextToken();
	if(checkName("int")) {
		inc();

		T = getNextToken();
		if(!checkType("ID")) error("ID");
		inc();


		T = getNextToken();
		if(!checkName("[")) error("[");
		inc();

		T = getNextToken();
		if(!checkType("NUM")) error("NUM");
		inc();

		T = getNextToken();
		if(!checkName("]")) error("]");
		inc();

		T = getNextToken();
		if(!checkName(";")) error(";");
		inc();
	}

}

void stmt() {

	T = getNextToken();
	if(!checkType("ID")) error("ID");
	inc();

	T = getNextToken();
	if(!checkName("=")) error("=");
	inc();

	T = getNextToken();
	if(!checkType("NUM")) error("NUM");
	inc();

	T = getNextToken();
	if(!checkName(";")) error(";");
	inc();

}

void main() {

	input = fopen("input.c", "r");

	fseek(input, 0, SEEK_END);
	size = ftell(input);

	fseek(input, 0, 0);
	fp = 0;
	idx = 0;

	printf("Displaying Tokens generated\n");
	
	while(fp < size){
		T = getNextToken();
		if(T) {
			printToken(T);
			fp += strlen(T->name);
		}
	}

	fp = 0;

	displayST();
	

	func_decl();
  printf("\nSuccess\n");
	if(fp == size) {
		printf("\nSuccess\n");
		displayST();
	}
	else
		printf("\nError. Unexpected tokens at the end of func_decl\n");

}