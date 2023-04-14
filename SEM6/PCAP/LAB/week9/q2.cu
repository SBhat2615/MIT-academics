#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void mulA(int *a, int* b, int* c, int wa, int wb)
{
	int ridA = threadIdx.x;
	int sum;
	for(int cidB = 0; cidB < wb; cidB++){
		sum = 0;
		for(int i = 0; i < wa; i++){
			sum += (a[ridA*wa + i] * b[i*wb + cidB]);
		}
		c[ridA*wb + cidB] = sum;
	}
}


int main(void){
	int *a, *b, *c, ha, wa, hb, wb, i, j;
	int *d_a, *d_b, *d_c;

	printf("Enter row and column for matrix A: ");
	scanf("%d%d", &ha, &wa);
	printf("Enter row and column for matrix B: ");
	scanf("%d%d", &hb, &wb);

	int size1 = sizeof(int)*ha*wa;
	int size2 = sizeof(int)*hb*wb;
	if(wa != hb){
		printf("Error in size\n");
		return -1;
	}
	int size3 = sizeof(int)*ha*wb;
	a = (int*)malloc(size1);
	b = (int*)malloc(size2);
	c = (int*)malloc(size3);

	printf("Enter input matrix A:\n");
	for(i = 0; i < ha*wa; i++)
	scanf("%d", &a[i]);
	printf("Enter input matrix B:\n");
	for(i = 0; i < hb*wb; i++)
	scanf("%d", &b[i]);

	cudaMalloc((void**)&d_a, size1);
	cudaMalloc((void**)&d_b, size2);
	cudaMalloc((void**)&d_c, size3);

	cudaMemcpy(d_a, a, size1, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, size2, cudaMemcpyHostToDevice);

	// ha threads
	mulA<<<1, ha>>>(d_a, d_b, d_c, wa, wb);
	
	// wb threads


	cudaMemcpy(c, d_c, size3, cudaMemcpyDeviceToHost);
	printf("Resultant matrix:\n");
	for(i = 0; i < ha; i++){
		for(j = 0; j < wb; j++)
			printf("%d\t", c[i*wb+j]);
		printf("\n");
	}
	getchar();
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}

/*

a)



b)



c)



*/