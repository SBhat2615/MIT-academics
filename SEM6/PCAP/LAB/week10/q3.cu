#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void program3(int *a, int* b, int n)
{
	int rid = threadIdx.x;
	for(int cid = 0; cid < n; cid++){
		if(rid != n-1 || cid != n-1 || rid != 0 || cid != 0)
			// Change code to write 1's complement
			// b[rid*n + cid] = a[rid*n + cid];
		}
	}
}


int main(void){
	int *a, *b, m, n, i, j;
	int *d_a, *d_b;

	printf("Enter the value of m: ");
	scanf("%d", &m);
	printf("Enter the value of n: ");
	scanf("%d", &n);

	int size = sizeof(int)*m*n;
	a = (int*)malloc(size);
	b = (int*)malloc(size);

	printf("Enter input matrix A:\n");
	for(i = 0; i < m*n; i++)
	scanf("%d", &a[i]);

	cudaMalloc((void**)&d_a, size);
	cudaMalloc((void**)&d_b, size);
	cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

	// m threads
	program3<<<1, m>>>(d_a, d_b, n);

	cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost);
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