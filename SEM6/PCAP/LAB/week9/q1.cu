#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void addA(int *a, int* b, int* c, int n)
{
	int rid = threadIdx.x;
	for(int cid = 0; cid < n; cid++){
		c[rid*n + cid] = a[rid*n + cid] + b[rid*n + cid];
	}
}

__global__ void addB(int *a, int* b, int* c, int m, int n)
{
	int cid = threadIdx.x;
	for(int rid = 0; rid < m; rid++){
		c[rid*n + cid] = a[rid*n + cid] + b[rid*n + cid];
	}
}

__global__ void addC(int *a, int* b, int* c)
{
	int tid = threadIdx.x;
	c[tid] = a[tid] + b[tid];
}

int main(void){
	int *a, *b, *c, m, n, i, j;
	int *d_a, *d_b, *d_c;

	printf("Enter the value of m: ");
	scanf("%d", &m);
	printf("Enter the value of n: ");
	scanf("%d", &n);

	int size = sizeof(int)*m*n;
	a = (int*)malloc(size);
	b = (int*)malloc(size);
	c = (int*)malloc(size);

	printf("Enter input matrix A:\n");
	for(i = 0; i < m*n; i++)
	scanf("%d", &a[i]);
	printf("Enter input matrix B:\n");
	for(i = 0; i < m*n; i++)
	scanf("%d", &b[i]);

	cudaMalloc((void**)&d_a, size);
	cudaMalloc((void**)&d_b, size);
	cudaMalloc((void**)&d_c, size);

	cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

	// m threads
	//addA<<<1, m>>>(d_a, d_b, d_c, n);

	// n threads
	//addB<<<1, n>>>(d_a, d_b, d_c, m, n);
	
	int threads = m*n;
	addC<<<1, threads>>>(d_a, d_b, d_c);

	cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
	printf("Resultant matrix:\n");
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++)
			printf("%d\t", c[i*n+j]);
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
Enter the value of m: 3
Enter the value of n: 2
Enter input matrix A:
2 3 4 5 6 7
Enter input matrix B:
6 7 8 9 10 11
Resultant matrix:
8	10	
12	14	
16	18


b)
Enter the value of m: 2
Enter the value of n: 3
Enter input matrix A:
2 3 4 5 6 7
Enter input matrix B:
5 6 7 8 9 10
Resultant matrix:
7	9	11	
13	15	17


c)
Enter the value of m: 2
Enter the value of n: 4
Enter input matrix A:
2 4 5 6 7 9 3 1
Enter input matrix B:
8 3 9 2 5 6 7 3
Resultant matrix:
10	7	14	8	
12	15	10	4


*/