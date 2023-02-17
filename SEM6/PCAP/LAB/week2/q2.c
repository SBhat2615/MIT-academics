#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int rank,size,number;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	if(rank==0)
	{
		for(int i = 1; i <= size-1; i++){
			number = i * 10;
			MPI_Send(&number, 1, MPI_INT, i, i, MPI_COMM_WORLD);
		}
	}
	else
	{
		MPI_Recv(&number, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
		printf("In process with rank %d, number received %d\n", rank, number);

	}
	MPI_Finalize();
	return 0;
}

/*

OUTPUT:
In process with rank 3, number received 30
In process with rank 4, number received 40
In process with rank 5, number received 50
In process with rank 6, number received 60
In process with rank 7, number received 70
In process with rank 1, number received 10
In process with rank 2, number received 20

*/