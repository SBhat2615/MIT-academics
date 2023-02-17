#include "mpi.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
	int rank, size, chunk, length, N, count = 0, count_p[4], t_count = 0;
	char s[20], s2[20];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank==0)
	{
		N = size;
		printf("Enter a string:\n");
		gets(s);
		length = strlen(s);
		chunk = length/size;
	}
	MPI_Bcast(&chunk, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(s, chunk, MPI_CHAR, s2, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
	for(int i = 0; i < chunk; i++){
		//printf("In rank %d string %c\n", rank, s2[i]);
		if(s2[i] != 'a' && s2[i] != 'e' && s2[i] != 'i' && s2[i] != 'o' && s2[i] != 'u')
			count += 1;
	}
	//printf("In rank %d count %d\n", rank, count);
	MPI_Gather(&count, 1, MPI_FLOAT, count_p, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	if(rank == 0)
	{
		printf("The Result gathered in the root\n");
		for(int i=0; i<N; i++){
			t_count += count_p[i];
			printf("%d\t",count_p[i]);
		}
		printf("\n");
		printf("Total vowel count = %d\n", t_count);
	}
	MPI_Finalize();
	return 0;
}

/*

Enter a string:
parallelprogrammingg
The Result gathered in the root
3	4	3	4	
Total vowel count = 14

*/