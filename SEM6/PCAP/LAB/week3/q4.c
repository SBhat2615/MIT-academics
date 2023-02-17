#include "mpi.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
	int rank, size, chunk, length, N;
	char s1[20], s2[20], s3[20], s4[20];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank==0)
	{
		N = size;
		printf("Enter string 1:\n");
		gets(s1);
		printf("Enter string 2:\n");
		gets(s2);
		length = strlen(s1);
		chunk = length/size;
	}
	MPI_Bcast(&chunk, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(s1, chunk, MPI_CHAR, s3, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Scatter(s2, chunk, MPI_CHAR, s4, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
	// for(int i = 0; i < chunk; i++){
	// 	printf("Rank %d, value = %c\n", rank, s3[i]);
	// 	printf("Rank %d, value = %c\n", rank, s4[i]);
	// }
	char resultant[40], res[40];
	int j = 0;
	for(int i = 0; i < chunk; i++){
		resultant[j++] = s3[i];
		resultant[j++] = s4[i];
	}
	resultant[j] = '\0';
	//puts(resultant);
	MPI_Bcast(&j, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Gather(resultant, chunk*2, MPI_CHAR, res, chunk*2, MPI_CHAR, 0, MPI_COMM_WORLD);
	if(rank == 0)
	{
		printf("The Result gathered in the root\n");
		for(int i = 0; i < 2*length; i++){
			printf("%c", res[i]);
		}
		printf("\n");
	}
	MPI_Finalize();
	return 0;
}

/*



*/