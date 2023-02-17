#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
	int rank, size, x = 2;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank%2 == 0)
		printf("Hello from process with rank %d\n", rank);
	else
		printf("World from process with rank %d\n", rank);
	MPI_Finalize();
	
}