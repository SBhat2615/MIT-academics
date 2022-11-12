#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX_SIZE 44
int getNextNumber=0;
char s[100];
int i;

char is_keywords[100][100]={"auto","break","case","char","const","continue","default","do",
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


typedef struct lexeme{
  char token_type[20];
  char lexeme_name[20];
  char data_type[20];
  int size;
  int no_of_args;
  char return_type[20];
}lexeme;

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
  token_array[token_counter].index = ++token_counter;
  
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
    s[i++]=ca;    // Store lexeme temporarily for comparision
    // String literal condition
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
    // Spaces
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

struct ListElement{
  struct lexeme t;
  struct ListElement *next;
};

struct ListElement *TABLE[44];
int TableLength=1;
void initialize()
{
  for(int i=0;i<44;i++)
    TABLE[i]=NULL;
}

void display_lexeme(lexeme t)
{
  printf("<%s,%s,%s,%d,%d,%s>",t.token_type,t.lexeme_name,t.data_type,t.size,t.no_of_args,t.return_type);
}
void display_table()
{
  printf("Global symbol table:\n");
  struct ListElement *pointer=TABLE[0];
  while(pointer!=NULL)
  {
    display_lexeme(pointer->t);
    pointer=pointer->next;
  }
  printf("\n\n");
  int count=1;
  while(TABLE[count]!=NULL)
  {
    struct ListElement *pointer=TABLE[count++];
  while(pointer!=NULL)
  {
    display_lexeme(pointer->t);
    pointer=pointer->next;
  }
  printf("\n\n");
  }
}

int hash(char *str)
{
  int h=0;
  for(int i=0;str[i]!='\0';i++)
  {
    h+=str[i];
  }
  return h%MAX_SIZE;
}

int search(char *str)
{
  int count=0;
  struct ListElement *pointer=TABLE[count];
  while(pointer!=NULL)
  {
    while(pointer!=NULL)
    {
      if(strcmp((pointer->t).lexeme_name,str)==0)
        return 1;
      pointer=pointer->next;
    }
    struct ListElement *pointer=TABLE[++count];
  }
  return 0;
}

void insert_hash(struct lexeme t)
{
  if(search(t.lexeme_name)==1)
    return;
  int val=hash(t.lexeme_name);
  struct ListElement *cur=(struct ListElement*)malloc(sizeof(struct ListElement));
    cur->t=t;
    cur->next=NULL;
    if(TABLE[val]==NULL)
    {
      TABLE[val]=cur;
    }
    else
    {
      struct ListElement *ele=TABLE[val];
      while(ele->next!=NULL)
        ele=ele->next;
      ele->next=cur;
      
    }

}

char return_types[10][10]={"void","int","double","long","struct","char","bool"};
int is_return_type(char *str)
{
  for(int i=0;i<7;i++)
    if(strcmp(return_types[i],str)==0)
      return 1;
  return 0;
}
char data_types[10][10]={"int","float","double","long","char","bool"};
int is_data_type(char *str)
{
  for(int i=0;i<6;i++)
    if(strcmp(data_types[i],str)==0)
      return 1;
  return 0;
}

int check_variable_declaration(int from)
{
  // printf("Inside vaarible: %s\n",token_array[from].token_name);
  char *str1="id";
  char *str2="[";
  char *str3="]";
  char *str4="num";
  if((token_counter-from)>=4)
  {
    if(is_data_type(token_array[from].token_name) &&
      (strcmp(str1,token_array[from+1].type)==0) &&
      (strcmp(token_array[from+2].token_name,str2)==0) &&
      (strcmp(str4,token_array[from+3].type)==0) &&
      (strcmp(token_array[from+4].token_name,str3)==0))
      {printf("returning from hereTWO");return 2;}
  }
  else if((token_counter-from)>=1)
  {
    if(is_data_type(token_array[from].token_name) &&
      (strcmp(str1,token_array[from+1].type)==0))
      {printf("returning from hereONE");return 1;}
  }
  else
    return 0;
}

int check_function_declaration(int from)
{
  char *str1="id";
  char *str2="(";
  if(is_return_type(token_array[from].token_name) &&
      (strcmp(str1,token_array[from+1].type)==0) &&
      (strcmp(str2,token_array[from+2].token_name)==0))
    return 1;
  return 0;    
}
int table_counter=1;

int give_size(char *str)
{
  char *str1="int";
  char *str2="double";
  char *str3="long";
  char *str4="char";
  char *str5="float";

  char *str6="bool";
  if(strcmp(str,str1)==0)
    return sizeof(int);
  if(strcmp(str,str2)==0)
    return sizeof(double);
  if(strcmp(str,str3)==0)
    return sizeof(long);
  if(strcmp(str,str4)==0)
    return sizeof(char);
  if(strcmp(str,str5)==0)
    return sizeof(float);
  if(strcmp(str,str6)==0)
    return sizeof(bool);
  
  
}
int count_comma(int from)
{
  int count=0;
  char *str=")";
  char *comma=",";
  while(strcmp(token_array[from].token_name,str)!=0)
  {
    if(strcmp(token_array[from++].token_name,comma)==0)
      count++;
  }
  return count+1;
}
void spaces(int n)
{
  for(int i=0;i<n;i++)
    printf(" ");
}
void print_format(char *a, char *b, char *c, int size, int no, char *d)
{
  int maxx=5;
  printf("%s ",a);spaces(maxx-strlen(a));
  printf("%s ",b);spaces(maxx-strlen(b));
  printf("%s ",c);spaces(maxx-strlen(c));
  printf("%d ",size);spaces(maxx);
  printf("%d ",no);spaces(maxx);
  printf("%s ",d);spaces(maxx-strlen(d));
}
int main()
{
  create_all_tokens();
  for(int i=0;i<token_counter;i++)
  {
    int tempp=check_variable_declaration(i);
    if(check_function_declaration(i))
    {
      printf("\nfunction found!!!!!\n");
      int noargs=count_comma(i+3);
      lexeme tt;
      char *str="function";
      strcpy(tt.lexeme_name,token_array[i+1].token_name);
      strcpy(tt.token_type,str);
      strcpy(tt.return_type,token_array[i].token_name);
      tt.size=0;
      tt.no_of_args=noargs;
      tt.data_type[0]='\0';
      insert_hash(tt);
      display_lexeme(tt);
      char *temp=")";
      while(strcmp(temp,token_array[i].token_name)!=0)
        i++;
    }
    else if(check_variable_declaration(i))
    {
      //printf("\nvariable found!!!!!\n");
      lexeme tt;
      // char *str=strcat(token_array[i].token_name," array");
      strcpy(tt.lexeme_name,token_array[i+1].token_name);
      strcpy(tt.token_type,token_array[i+1].type);
      strcpy(tt.data_type,token_array[i].token_name);
      tt.size=give_size(token_array[i].token_name);
      tt.no_of_args=0;
      tt.return_type[0]='\0';
      insert_hash(tt);
      display_lexeme(tt);
    }
    else if(tempp==1)
    {
      //printf("\nvariable found!!!!!\n");
      lexeme tt;
      strcpy(tt.lexeme_name,token_array[i+1].token_name);
      strcpy(tt.token_type,token_array[i+1].type);
      strcpy(tt.data_type,token_array[i].token_name);
      tt.size=give_size(token_array[i].token_name);
      tt.no_of_args=0;
      tt.return_type[0]='\0';
      insert_hash(tt);
      display_lexeme(tt);
    }
  }
  display_table();
  //printf("!!!!!!!!!!!!!!!\n");
  for(int i=0;i<44;i++)
  {
    if(TABLE[i]!=NULL)
    {
      display_lexeme(TABLE[i]->t);
      printf("\n");
    }
  }
  return 0;
}