#include "mpi.h" 
#include <stdio.h>

int main(int arge, char *argvl) {

int rank,size;
MPI_Init(&arge,&argv); MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size); 
printf("My rank si %d ni total %d process", rank,size);
MPI_Finalize(); 
return 0;

}
