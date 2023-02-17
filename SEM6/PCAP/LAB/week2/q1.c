#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int rank,size,length;
	char word[20], word2[20];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	if(rank==0)
	{
		printf("Enter a word in master process: ");
		scanf("%s", word);
		length = strlen(word);
		MPI_Ssend(&length,1,MPI_INT,1,1,MPI_COMM_WORLD);
		MPI_Ssend(word,length,MPI_CHAR,1,1,MPI_COMM_WORLD);
		MPI_Recv(word2,length,MPI_CHAR,1,1,MPI_COMM_WORLD,&status);
		fprintf(stdout,"In master process. After toggle in process 1 : %s\n",word2);
		fflush(stdout);
	}
	else
	{
		MPI_Recv(&length,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		MPI_Recv(word2,length,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		for(int i = 0; i < length; i++){
			if(word2[i] >= 'a' && word2[i] <= 'z')
				word2[i] -= 32;
			else if(word2[i] >= 'A' && word2[i] <= 'Z')
				word2[i] += 32;
		}
		MPI_Ssend(word2, length, MPI_CHAR, 0, 1 , MPI_COMM_WORLD);
		//fprintf(stdout,"In process 1. After toggle %s\n",word2);
		//fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}

/*

OUTPUT:
Enter a word in master process: ManIPaL
In master process. After toggle in process 1 : mANipAl

*/