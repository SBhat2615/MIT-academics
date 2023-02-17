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
	if(rank == 0)
	{
		printf("Enter a value: ");
		scanf("%d", &number);
		MPI_Send(&number, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		//printf("size = %d\n", size);
		MPI_Recv(&number, 1, MPI_INT, size-1, 1, MPI_COMM_WORLD, &status);
		printf("In master process, Value received = %d\n", number);
	}
	else
	{
		if(rank == size-1){
			MPI_Recv(&number, 1, MPI_INT, rank-1, 1, MPI_COMM_WORLD, &status);
			printf("In process with rank %d, Value received = %d\t", rank, number);
			number += 1;
			printf("Value to be sent = %d, To process %d\n", number, 0);
			MPI_Send(&number, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		}
		else{
			MPI_Recv(&number, 1, MPI_INT, rank-1, 1, MPI_COMM_WORLD, &status);
			printf("In process with rank %d, Value received = %d\t", rank, number);
			number += 1;
			printf("Value to be sent = %d, To process %d\n", number, rank+1);
			MPI_Send(&number, 1, MPI_INT, rank+1, 1, MPI_COMM_WORLD);
		}
	}
	MPI_Finalize();
	return 0;
}

/*

OUTPUT:

Enter a value: 35
In process with rank 1, Value received = 35	Value to be sent = 36, To process 2
In process with rank 2, Value received = 36	Value to be sent = 37, To process 3
In process with rank 3, Value received = 37	Value to be sent = 38, To process 4
In process with rank 4, Value received = 38	Value to be sent = 39, To process 0
In master process, Value received = 39

*/