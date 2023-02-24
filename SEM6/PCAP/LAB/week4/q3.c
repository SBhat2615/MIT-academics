#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
	int rank, size,	search, count = 0, total_count = 0;
	int arr[3][3], b[3];

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0){
		printf("Enter elements of 3x3 matrix:\n");
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				scanf("%d", &arr[i][j]);
			}
		}
		printf("Enter element to be searched: ");
		scanf("%d", &search);
	}

	MPI_Scatter(arr, 3, MPI_INT, b, 3, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&search, 1, MPI_INT, 0, MPI_COMM_WORLD);

	for(int i = 0; i < 3; i++){
		if(b[i] == search){
			count += 1;
		}
	}

	MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0)
		printf("Total count = %d\n", total_count);
	
	MPI_Finalize();
	exit(0);
}