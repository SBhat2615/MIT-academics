#include <stdio.h>
#include <stdlib.h>

void comments(){
	FILE *fa, *fb;
	char *fname;
  char ca, cb;

  printf("Hello from comments\n");
	//printf("\nEnter file to read - ");
	//scanf("%s", fname);
  fname = "spacesRemoved.c";
	fa = fopen(fname, "r");
  if(!fa){
		perror("\nFiles don't exist!\n");
		//return -1;
	}

	//printf("\nEnter file to write - ");
	//scanf("%s", fname);
  fname = "commentsRemoved.c";
	fb = fopen(fname, "w+");
  if(!fb){
		perror("\nFiles don't exist!\n");
		//return -1;
	}

	ca = fgetc(fa);
	while(ca != EOF){

		if(ca == '/'){
			cb = fgetc(fa);
			if(cb == '/'){
				while(ca != '\n')
					ca = fgetc(fa);
			}
			else if(cb == '*'){
				do{
					while(ca != '*'){
						ca = fgetc(fa);
					}
					ca = fgetc(fa);
				}while(ca !='/');
				
			}
			else
			{
				fputc(ca, fb);
				fputc(ca, fa);
			}
			
		}
		else
			fputc(ca, fb);
		
		ca = fgetc(fa);
	}

	fclose(fa);
	fclose(fb);
	exit(0);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
	FILE *fa, *fb;
	char fname[100], c, cb;

	printf("\nEnter file to read - ");
	scanf("%s", fname);
	fa = fopen(fname, "r");

	printf("\nEnter file to write - ");
	scanf("%s", fname);
	fb = fopen(fname, "w+");
	
	if(fa == NULL){
		printf("Cannot open file 1\n");
		exit(0);
	}
	if(fb == NULL){
		printf("Cannot open file 2\n");
		exit(0);
	}

	c = fgetc(fa);
	while(c != EOF){

		if(c == '/'){
			cb = fgetc(fa);
			if(cb == '/'){
				while(c != '\n')
					c = fgetc(fa);
			}
			else if(cb == '*'){
				do{
					while(c != '*'){
						c = fgetc(fa);
					}
					c = fgetc(fa);
				}while(c!='/');
				
			}
			else
			{
				fputc(c, fb);
				fputc(c, fa);
			}
			
		}
		else
			fputc(c, fb);
		
		c = fgetc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}
*/