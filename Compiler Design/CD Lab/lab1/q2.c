#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fptr1, *fptr2;
	char filename[100], c;
	printf("Enter the filename for reading: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	printf("Enter the filename to store: \n");
	scanf("%s", filename);
	fptr2 = fopen(filename, "w+");

	fseek(fptr1, 0, SEEK_END);
	int pos = ftell(fptr1)-1;
	int offset = -1;
	int i = 0, size = ftell(fptr1);
	while (i < pos)
	{
		fseek(fptr1, --offset, SEEK_END);
		c = fgetc(fptr1);
		fputc(c, fptr2);
		i++;
	}
	fputc('\n', fptr2);
	printf("Reverse contents copied to %s\n", filename);
	printf("Size of file : %d\n", size);
	fclose(fptr1);
	fclose(fptr2);
	return 0;
}