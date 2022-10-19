
#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *fa, *fb;
	char fname[100], ca, cb;

	printf("\nEnter file to read - ");
	scanf("%s", fname);
	fa = fopen(fname, "r");
	ca = fgetc(fa);

	printf("\nEnter file to write - ");
	scanf("%s", fname);

	fb = fopen(fname, "w+");
	
	if(!fa){
		perror("\nFiles don't exist!\n");
		return -1;
	}
	
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
					ca = fgetc(fb);
				}while(ca !='/');
				
			}
			else
			{
				fputc(ca, fa);
				fputc(ca, fb);
			}
			
		}
		else fputc(ca, fa);
		
		ca = fgetc(fb);
		
		
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
	FILE *fptr1, *fptr2;
	char fname[100], c, c1;

	printf("\nEnter file to read - ");
	scanf("%s", fname);
	fptr1 = fopen(fname, "r");

	printf("\nEnter file to write - ");
	scanf("%s", fname);
	fptr2 = fopen(fname, "w+");
	
	if(fptr1 == NULL){
		printf("Cannot open file 1\n");
		exit(0);
	}
	if(fptr2 == NULL){
		printf("Cannot open file 2\n");
		exit(0);
	}

	c = fgetc(fptr1);
	while(c != EOF){

		if(c == '/'){
			c1 = fgetc(fptr1);
			if(c1 == '/'){
				while(c != '\n')
					c = fgetc(fptr1);
			}
			else if(c1 == '*'){
				do{
					while(c != '*'){
						c = fgetc(fptr1);
					}
					c = fgetc(fptr1);
				}while(c!='/');
				
			}
			else
			{
				fputc(c, fptr2);
				fputc(c, fptr1);
			}
			
		}
		else
			fputc(c, fptr2);
		
		c = fgetc(fptr1);
	}
	fclose(fptr1);
	fclose(fptr2);
	return 0;
}
*/