#include <stdio.h>
#include <stdlib.h>

int main()
{
	int countLines = 0, countChars = 0;
	FILE *fptr1, *fptr2;
	char filename[100], c;
	printf("Enter the filename to open for reading: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	c = fgetc(fptr1);
	while(c != EOF){
		if(c != ' ' && c != '\n')
			countChars++;
		if(c == '\n')
			countLines++;
		c = fgetc(fptr1);
	}
	printf("Number of lines: %d\nNumber of characters: %d\n", countLines, countChars);
	fclose(fptr1);
}