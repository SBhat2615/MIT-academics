#include <stdio.h>
#include <mpi.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[]){
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	char string1[] = "HeLLo";
	char string2[5], string3[5];
	MPI_Status status;
	/*
	if(rank == 0){
		printf("String after toggle = %s\n", string);
	}
	else{
		printf("Character %c toggled by process with rank = %d\n", string[rank-1], rank);
		if(string[rank-1] > 95)
			toupper(string[rank-1]);
		else
			tolower(string[rank-1]);
	}
	*/
	int len;
	if(rank == 0){
		//len = strlen(string1);
		//MPI_Send(&len, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		for(int i = 1; i <= 5; i++){
			MPI_Send(string1, 5, MPI_CHAR, i, i, MPI_COMM_WORLD);
		}
		for(int i = 1; i <= 5; i++){
			MPI_Recv(string1, 5, MPI_CHAR, i, i, MPI_COMM_WORLD, &status);
			string3[i-1] = string1[i-1];
		}
		printf("String after all toggle: %s\n", string3);
	}
	else{
		//MPI_Recv(&len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		
		MPI_Recv(string2, 5, MPI_CHAR, 0, rank, MPI_COMM_WORLD, &status);

		if(string2[rank-1] >= 'a' && string2[rank-1] <= 'z'){
			string2[rank-1] -= 32;
			printf("Character toggle by process with rank %d\nToggled character : %c\n", rank, string2[rank-1]);
		}
		else{
			string2[rank-1] += 32;
			printf("Character toggle by process with rank %d\nToggled character : %c\n", rank, string2[rank-1]);
		}
		//printf("String after toggle: %s\n", string2);
		MPI_Send(string2, 5, MPI_CHAR, 0, rank, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
}