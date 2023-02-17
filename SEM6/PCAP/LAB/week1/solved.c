#include <stdio.h>
#include <mpi.h>

int main(int argc, char const *argv[]){
	int rank, size, x = 2;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("This is process with rank %d and pow(%d, %d) = ", rank, x, rank);
	MPI_Finalize();
}