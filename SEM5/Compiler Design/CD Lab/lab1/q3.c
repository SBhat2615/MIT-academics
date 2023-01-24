#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fptr1, *fptr2, *fptr3;
	char filename[100], c1, c2;
	printf("Enter the 1st filename: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");
	if (fptr1 == NULL)
	{
		printf("Cannot open file 1 %s \n", filename);
		exit(0);
	}
	printf("Enter the 2nd filename: \n");
	scanf("%s", filename);
	fptr2 = fopen(filename, "r");
	if (fptr2 == NULL)
	{
		printf("Cannot open file 2 %s \n", filename);
		exit(0);
	}
	printf("Enter filename to write: \n");
	scanf("%s", filename);
	fptr3 = fopen(filename, "w+");

	c1 = fgetc(fptr1);
	c2 = fgetc(fptr2);

	while(c1 != EOF || c2 != EOF){
		if(c1 != EOF){
			while(c1 != '\n'){
				fputc(c1, fptr3);
				c1 = fgetc(fptr1);
			}
			fputc('\n', fptr3);//Else printed in 1 line
			c1 = fgetc(fptr1);//Useful after c1='\n'
		}
		if(c2 != EOF){
			while(c2 != '\n'){
				fputc(c2, fptr3);
				c2 = fgetc(fptr2);
			}
			fputc('\n', fptr3);//Else printed in 1 line
			c2 = fgetc(fptr2);//Useful after c1='\n'
		}
	}

	printf("Lines merged from 2 files\n");
	fclose(fptr1);
	fclose(fptr2);
	fclose(fptr3);
	return 0;
}