#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *fptr1, *fptr2;
	char filename[100], c;

	printf("Enter the source file:\n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");
	if(fptr1 == NULL){
		printf("Cannot open file 1\n");
		exit(0);
	}
	printf("Enter the destination file:\n");
	scanf("%s", filename);
	fptr2 = fopen(filename, "w+");
	if(fptr2 == NULL){
		printf("Cannot open file 2\n");
		exit(0);
	}

	c = fgetc(fptr1);
	int count = 0;
	while(c != EOF){
		while(c == ' ' || c == '\t'){
			count = 1;
			c = fgetc(fptr1);
		}
		if(count == 1){
			fputc(' ', fptr2);
			count = 0;
		}
		fputc(c, fptr2);
		c = fgetc(fptr1);
	}
	fclose(fptr1);
	fclose(fptr2);
}