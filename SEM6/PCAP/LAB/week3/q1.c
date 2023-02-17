#include "mpi.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
	int rank,size,N,A[10],B[10], c, i, fact_sum = 0;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		N=size;
		fprintf(stdout,"Enter %d values:\n",N);
		fflush(stdout);
		for(i=0; i<N; i++)
			scanf("%d",&A[i]);
	}
	MPI_Scatter(A,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
	fprintf(stdout,"I have received %d in process %d\n",c,rank);
	fflush(stdout);
	int fact = 1;
	for(int i = c; i >0; i--){
		fact = fact * i;
	}
	MPI_Gather(&fact,1,MPI_INT,B,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("The Result gathered in the root\n");
		for(i=0; i<N; i++){
			fact_sum += B[i];
			printf("%d \t",B[i]);	
		}
		printf("\n");
		printf("Sum of factorial = %d\n", fact_sum);
	}
	MPI_Finalize();
	return 0;
}

/*

Enter 4 values:
2 3 4 5
I have received 2 in process 0
The Result gathered in the root
2 	6 	24 	120 	
Sum of factorial = 152
I have received 3 in process 1
I have received 4 in process 2
I have received 5 in process 3


*/