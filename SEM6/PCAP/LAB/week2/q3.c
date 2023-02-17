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
	int a[size];
	if(rank == 0)
	{
		printf("Enter array: ");
		for(int i = 1; i <= size-1; i++){
			scanf("%d", &a[i]);
			MPI_Send(&a[i], 1, MPI_INT, i, i, MPI_COMM_WORLD);
		}
		printf("\n");
	}
	else
	{
		MPI_Recv(&number, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
		if (rank % 2 == 0){
			printf("In process with rank %d, number received %d\n", rank, number);
			printf("Square of that number: %d\n\n", number*number);
		}
		else{
			printf("In process with rank %d, number received %d\n", rank, number);
			printf("Cube of that number: %d\n\n", number*number*number);
		}

	}
	MPI_Finalize();
	return 0;
}

/*

OUTPUT:
Enter array: 2 5 4 7 3

In process with rank 1, number received 2
Cube of that number: 8

In process with rank 2, number received 5
Square of that number: 25

In process with rank 3, number received 4
Cube of that number: 64

In process with rank 4, number received 7
Square of that number: 49

In process with rank 5, number received 3
Cube of that number: 27

*/  