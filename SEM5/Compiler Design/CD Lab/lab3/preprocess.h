#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *directives[] = {"#define","#include"};

int isDirective(const char *str){
	for(int i = 0; i<sizeof(directives)/sizeof(char*); i++){
		if(strncmp(str,directives[i],strlen(directives[i])) == 0){
			return 1;
		}	
	}
	return 0;
}

int preprocessor(){
  FILE *fa, *fb;
  char *filename;
  char c, c1;
  char buff[2048];

  printf("Hello from preprocessor");

	//printf("Enter the source file:\n");
	//scanf("%s", filename);
  filename = "commentsRemoved.c";
	fa = fopen(filename, "r");
	if(fa == NULL){
		printf("Cannot open file 1\n");
		exit(0);
	}

	//printf("Enter the destination file:\n");
	//scanf("%s", filename);
  filename = "pdRemoved.c";
	fb = fopen(filename, "w+");
	if(fb == NULL){
		printf("Cannot open file 2\n");
		exit(0);
	}

	while(fgets(buff, 2048, fa)){
		if(!isDirective(buff))
			fputs(buff,fb);
	}

	fclose(fa);
	fclose(fb);
}