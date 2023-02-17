#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int num1, num2;
	num1 = 13;
	num2 = 5;
	switch(rank){
		case 0:
			printf("Process with rank: %d and Sum of two numbers: %d\n", rank, num1+num2);
			break;	
		case 1:
			printf("Process with rank: %d and Difference of two numbers: %d\n", rank, num1-num2);
			break;
		case 2:
			printf("Process with rank: %d and Multiplication of two numbers: %d\n", rank, num1*num2);
			break;
		case 3:
			printf("Process with rank: %d and Division of two numbers: %d\n", rank, num1/num2);
			break;
	}
	MPI_Finalize();
}
