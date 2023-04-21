#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void program2(int *a, int* b, int* c, int n)
{
	int rid = threadIdx.x;
	for(int cid = 0; cid < n; cid++){
		for(int i = rid; i > 0; i--){
			c[rid*n + cid] *= c[rid*n + cid];
		}
	}
}


int main(void){
	int *a, m, n, i, j;
	int *d_a;

	printf("Enter the value of m: ");
	scanf("%d", &m);
	printf("Enter the value of n: ");
	scanf("%d", &n);

	int size = sizeof(int)*m*n;
	a = (int*)malloc(size);

	printf("Enter input matrix A:\n");
	for(i = 0; i < m*n; i++)
	scanf("%d", &a[i]);

	cudaMalloc((void**)&d_a, size);

	cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

	// m threads
	program2<<<1, m>>>(d_a, n);

	cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
	printf("Resultant matrix:\n");
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++)
			printf("%d\t", c[i*n+j]);
		printf("\n");
	}

	getchar();
	cudaFree(d_a);
	return 0;
}

/*




*/