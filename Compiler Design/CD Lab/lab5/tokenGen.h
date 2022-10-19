#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 50
int getNextNumber=0;
char s[100];
int i;

char is_keywords[50][20]={"auto","break","case","char","const","continue","default","do",
"double","else","enum","extern","float","for","goto","if","int","long","register","return",
"short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void",
"volatile","while","_Packed"};

char logical_operators[3][2]={"&&","||","!"};
char bitwise_operators[2]={'&','|'};
char relational_operators[6][2]={">","<","==",">=","<=","!="};
char operators[5]={'-','+','/','*','%'};
char brackets[6]={'{','}',']','(','[',')'};
char special[4]={'?',',',':',';'};

typedef struct token{
  char token_name[100];
  int index;
  unsigned int r,c; 
  char type[100];
}token;


token token_array[1000];
int token_counter=0;
void insert_token(int r,int c,char *type,char *name){
  if(strlen(name)==0)
    return;
  i=0;
  // printf("<%s,",name);
  // for(int j=0;j<(15-strlen(name));j++)
  //   printf(" ");
  // printf("%s,%d,%d>\n",type,r,c);
  strcpy(token_array[token_counter].token_name,name);
  strcpy(token_array[token_counter].type,type);
  token_array[token_counter].c=c;
  token_array[token_counter].r=r;
  token_array[token_counter].index=++token_counter;
  
  memset(s,0,100);
}

bool is_assignment_operator(char ch){
  return ch=='=';
}

bool is_keyword(){
  for(int i=0;i<33;i++)
    if(!strcmp(s,is_keywords[i]))
      return true;
  return false;
}

bool id(){
  for(int i=0;s[i]!='\0';i++) 
    if(!((s[i]-'0'<10 && s[i]-'0'>=0) || (s[i]>=65 && s[i]<=90) || (s[i]<=122 && s[i]>=97))) 
      return false;
  return true;
}

bool relop(){
  for(int i=0;i<6;i++)
    if(!strcmp(s,relational_operators[i]))
      return true;
  return false;
}

bool is_arithmetic_operator(char ch){
  for(int i=0;i<5;i++)
    if(ch==operators[i])
      return true;
  return false;
}

bool is_num(){
  bool flag=false;
  for(int i=0;s[i]!='\0';i++){
    if(s[i]=='.'){
      if(!flag) flag=true;
      else return false;
    }
    if(s[i]<48 || s[i]>57) return false;
  }
  return true;
}

bool is_digit(char ch){
  return ch>=48 && ch<=57;
}

bool logical(){
  for(int i=0;i<3;i++)
    if(!strcmp(s,logical_operators[i]))
      return true;
  return false;
}

bool is_bracket(char ch){
  for(int i=0;i<6;i++) if(ch==brackets[i]) return true;
  return false;
}

bool specialchar(char ch){
  for(int i=0;i<4;i++) if(special[i]==ch) return true;
  return false;
}

bool is_bitwise(char ch){
  for(int i=0;i<3;i++) if(bitwise_operators[i]==ch) return true;
  return false;
}

void throw_error(int r, int c){
  printf("Error found at r: %d c: %d",r, c);
  exit(0);
}

void create_all_tokens(){
  FILE *fa,*fb;
  int ca,cb,r=1,c=1;
  i=0;
  char *name;
  fa=fopen("input.c","r");
  ca=getc(fa);
  fb=fopen("output.c","w");
  if(fa==NULL || fb==NULL){
    printf("These files don't exist\n");
    exit(0);
  }
  while(ca!=EOF){
    s[i++]=ca;
    if(ca=='"'){
      insert_token(r,c,name,s);
      while((ca=getc(fa))!='"' && ca!=EOF){
        s[i++]=ca;
        c++;
      }
      c++;
      if(ca==EOF) throw_error(r,c);
      insert_token(r,c-i-1,"literal",s);
    }
    else if(ca==' '){
      s[--i]='\0';
      insert_token(r,c-i,name,s);
    }
    else if(ca=='\n'){
      s[0]='\\';
      s[1]='n';
      s[2]='\0';
      insert_token(r,c-i,name,s);
      r++,c=0;
    }
    else if(ca=='.'){
      if(i-2<0 || !is_digit(s[i-2])) throw_error(r,c);
      while(is_digit(ca=getc(fa))){
        s[i++]=ca;
        c++;
      }
      c++;
      if(!is_digit(s[i-1])) throw_error(r,c);
      fseek(fa,-1,SEEK_CUR);
      insert_token(r,c-i-1,"number",s);
      c--;
    }
    else if(is_bracket(ca)){
      s[--i]='\0';
      insert_token(r,c-i,name,s);
      char str[1]={ca};
      insert_token(r,c-1,"bracket",str);
    }
    else if(is_assignment_operator(ca)){
      s[--i]='\0';
      insert_token(r,c-i,name,s);
      char str[1]={ca};
      insert_token(r,c-1,"is_assignment_operator",str);
    }
    else if(is_arithmetic_operator(ca)){
      insert_token(r,c-i,name,s);
      char str[1]={ca};
      insert_token(r,c-1,"arithmetic",str);
    }
    else if(specialchar(ca)){
      s[--i]='\0';
      insert_token(r,c-i,name,s);
      char str[1]={ca};
      insert_token(r,c-1,"specialChar",str);
    }
    else if(logical() || is_bitwise(ca)){
      if(i==1) name="bitwise_operators";
      else name="logical";
    } 
    else if(is_num()) name="num";
    else if(relop()) name="relop";
    else if(is_keyword()) name="is_keyword";
    else if(id()) name="id";
    else{
      if(i==1) throw_error(r,c);
      insert_token(r,c-i,name,s);
      fseek(fa,-1,SEEK_CUR);
      c--;
    }
    ca=getc(fa);
    c++;
  }
  if(i) insert_token(r,c-i,name,s);

  
}

token getNextToken()
{
  return token_array[getNextNumber++];
}