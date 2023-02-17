#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[]){
	int rank, size, x = 2;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int power;
	power = pow(x, rank);
	printf("This is process with rank %d and pow(%d, %d) = %d\n", rank, x, rank, power);
	MPI_Finalize();
}