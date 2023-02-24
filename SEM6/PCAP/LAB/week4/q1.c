#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void ErrorHandler(int error_code);

int main(int argc, char* argv[])
{
	int rank, size, fact=1, factsum, i, error_code, numtasks;
	int c = 3;

	MPI_Init(&argc,&argv);

	MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	error_code = MPI_Comm_size(MPI_COMM_WORLD, NULL);

	ErrorHandler(error_code);


	// Actual code
	for(i=1; i<=rank+1; i++)
		fact = fact * i;

	MPI_Scan(&fact, &factsum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	if(rank == size-1)
		printf("Sum of all the factorial = %d\n",factsum);
	
	MPI_Finalize();
	exit(0);
}

void ErrorHandler(int error_code){
	if(error_code != MPI_SUCCESS){
		char str[100];
		int len, class;
		MPI_Error_class(error_code, &class);
		MPI_Error_string(error_code, str, &len);
		//fprintf(stderr, "%d %s\n", error_code, str);
		//MPI_Error_string(class, str, &len);
		//fprintf(stderr, "%d %s\n", class, str);
		fprintf(stderr, "This is the error function with %d and %s\n", class, str);
	}
}