#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void NextFit(int blockSize[], int m, int processSize[], int n)
{
	
	int allocation[n], j = 0;
	memset(allocation, -1, sizeof(allocation));
	for (int i = 0; i < n; i++) 
	{
		while (j < m) 
		{
			if (blockSize[j] >= processSize[i])
			{		
				allocation[i] = j;			
				blockSize[j] -= processSize[i];
				break;
			}
			j = (j + 1) % m;
		}
	}

	printf("\nProcess No.\tProcess Size\tBlock no.\n");
	for (int i = 0; i < n; i++)
	{
		printf(" %i\t\t", i+1);
		printf("%i\t\t", processSize[i]);
		if (allocation[i] != -1)
			printf("%i", allocation[i] + 1);
		else
			printf("Not Allocated");
		printf("\n");
	}
}

// Driver program
int main()
{
	int blockSize[] = { 5, 10, 20 };
	int processSize[] = { 10, 20, 5 };
	int m = sizeof(blockSize) / sizeof(blockSize[0]);
	int n = sizeof(processSize) / sizeof(processSize[0]);

	NextFit(blockSize, m, processSize, n);

	return 0;
}
