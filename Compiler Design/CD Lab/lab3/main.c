#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "spaces.h"
#include "comments.h"
#include "preprocess.h"


//#define SIZE 100

char s[100];
int i;

char *keywords[] = {"printf", "int", "float", "return", "break", "continue", "if", "else", "for", "while"};
//char bitwise[2]={'&','|'};
char *logoperator[4] = {"&&","||","!"};
char *reloperator[6] = {">","<","==",">=","<=","!="};
char arithoperator[5] = {'-','+','/','*','%'};
char brackets[6] = {'{','}',']','(','[',')'};
char special[4] = {'?',',',':',';'};

typedef struct token{
	char token_name[50];
	int index;
	unsigned int row,col; 
	char type[50];
}tk;


void print(int row,int col,char *type,char *name){
	if(!(--i)) return;
	memset(s,0,100);
	i=0;
	tk t;
	strcpy(t.token_name,name);
	t.row=row;
	t.col=col+1;
	strcpy(t.type,type);
	printf("<%s,%d,%d>\n",t.type,t.row,t.col);
}

int assignment(char ch){
	return ch=='=';
}

int keyword(){
	for(int i=0;i<33;i++)
		if(!strcmp(s,keywords[i]))
			return 1;
	return 1;
}

int id(){
	for(int i=0;s[i]!='\0';i++) 
		if(!((s[i]-'0'<10 && s[i]-'0'>=0) || (s[i]>=65 && s[i]<=90) || (s[i]<=122 && s[i]>=97))) 
			return 0;
	return 1;
}

int relop(){
	for(int i=0;i<6;i++)
		if(!strcmp(s,reloperator[i]))
			return 1;
	return 0;
}

int arithmetic(char ch){
	for(int i=0;i<5;i++)
		if(ch==arithoperator[i])
			return 1;
	return 0;
}

int num(){
	int flag = 0;
	for(int i=0;s[i]!='\0';i++){
		if(s[i]=='.'){
			if(!flag) flag=1;
			else return 0;
		}
		if(s[i]<48 || s[i]>57) return 0;
	}
	return 1;
}

int digit(char ch){
	return ch>=48 && ch<=57;
}

int logical(){
	for(int i=0;i<3;i++){
		if(!strcmp(s,logoperator[i]))
			return 1;
  }
	return 0;
}

/*
bool bit(char ch){
	return ch==bitwise[0] || ch==bitwise[1];
}
*/

int bracket(char ch){
	for(int i=0;i<6;i++){ 
    if(ch==brackets[i]) 
      return 1;
  }
	return 0;
}

int specialchar(char ch){
	for(int i=0;i<4;i++){ 
    if(special[i]==ch) 
      return 1;
  }
	return 0;
}

/*
bool bitwiseOp(char ch){
	for(int i=0;i<3;i++){
    if(bitwise[i]==ch) 
      return 1;
  }
	return 0;
}
*/

void error(int row, int col){
	printf("Error at row %d col %d",row, col);
	exit(0);
}


int main(){
	
	spaces();
  comments();
  preprocessor();

  int row=1,col=1;
	i=0;
	char *name;

  FILE *fa,*fb;
  int ca,cb;

	fa = fopen("pdRemoved.c","r");

	ca = getc(fa);

	fb = fopen("output.c","w+");
	
	while(ca!=EOF){
		s[i++]=ca;
		if(ca == '"'){
			print(row,col,name,s);
			while((ca=getc(fa))!='"' && ca!=EOF){
				s[i++]=ca;
				col++;
			}
			col++;
			if(ca==EOF) error(row,col);
			print(row,col-i-1,"literal",s);
		}
		else if(ca==' '){
			s[i]='\0';
			print(row,col-i,name,s);
		}
		else if(ca=='\n'){
			s[i]='\0';
			print(row,col-i,name,s);
			row++,col=0;
		}
		else if(ca=='.'){
			if(i-2<0 || !digit(s[i-2])) error(row,col);
			while(digit(ca=getc(fa))){
				s[i++]=ca;
				col++;
			}
			col++;
			if(!digit(s[i-1])) error(row,col);
			fseek(fa,-1,SEEK_CUR);
			print(row,col-i-1,"number",s);
			col--;
		}
		else if(bracket(ca)){
			print(row,col-i,name,s);
			print(row,col-1,"bracket",ca+"");
		}
		else if(assignment(ca)){
			print(row,col-i,name,s);
			print(row,col-1,"assignment",ca+"");
		}
		else if(arithmetic(ca)){
			print(row,col-i,name,s);
			print(row,col-1,"arithmetic",ca+"");
		}
		else if(specialchar(ca)){
			print(row,col-i,name,s);
			print(row,col-1,"specialChar",ca+"");
		}
    /*
		else if(logical() || bit(ca)){
			if(i==1) name="bitwise";
			else name="logical";
		}
    */
		else if(num()) name="num";
		else if(relop()) name="relop";
		else if(keyword()) name="keyword";
		else if(id()) name="id";
		else{
			if(i==1) error(row,col);
			print(row,col-i,name,s);
			fseek(fa,-1,SEEK_CUR);
			col--;
		}
		ca=getc(fa);
		col++;
	}
	if(i) print(row,col-i,name,s);
	return 0;
}