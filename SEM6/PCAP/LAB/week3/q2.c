#include "mpi.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
	int rank, size, N, M, A[20], C[20], c, i;
	float B[20];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		N=size;
		printf("Enter a value M: ");
		scanf("%d", &M);
		fprintf(stdout,"Enter %d values:\n",N*M);
		fflush(stdout);
		for(i=0; i<N*M; i++)
			scanf("%d",&A[i]);
	}
	MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(A,M,MPI_INT,C,M,MPI_INT,0,MPI_COMM_WORLD);
	
	int sum = 0;
	for(int i = 0; i < M; i++){
		sum += C[i];
	}
	float avg  = sum / M;
	printf("%.1f\n", avg);
	MPI_Gather(&avg,1,MPI_FLOAT,B,1,MPI_FLOAT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("The Result gathered in the root\n");
		for(i=0; i<N; i++)
		printf("%.1f\t",B[i]);
		printf("\n");
	}
	MPI_Finalize();
	return 0;
}

/*

Enter a value M: 2
Enter 8 values:
10 40 20 50 30 70 60 80
25.0
35.0
50.0
70.0
The Result gathered in the root
25.0	35.0	50.0	70.0

*/