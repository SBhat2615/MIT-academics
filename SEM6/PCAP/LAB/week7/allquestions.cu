#include <stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdlib.h>

__global__ void add(int *a, int *b, int *c)
{
	*c = *a + *b;
}

__global__ void add1(int* a, int* b, int* c)
{
	int tid = blockIdx.x;
	c[tid] = a[tid] + b[tid];
}

__global__ void add2(int* a, int* b, int* c)
{
	int tid = threadIdx.x;
	c[tid] = a[tid] + b[tid];
}

__global__ void question2(int* a, int* b, int* c, int N){
	int tid = blockIdx.x * blockDim.x + threadIdx.x;
	if(tid < N)
		c[tid] = a[tid] + b[tid];
}

__global__ void question3(float* N, float* M, float* P, int width, int mask_width){
	int tid = blockIdx.x * blockDim.x + threadIdx.x;
	float Pvalue = 0;
	int startpoint = tid - (mask_width/2);
	for(int j = 0; j < mask_width; j++){
		if(startpoint+j >=0 && startpoint+j < width){
			Pvalue += N[startpoint+j] * M[j];
		}
	}
	P[tid] = Pvalue;                                       
}

__global__ void question4(int* a, int* b){
	int tid = blockIdx.x * blockDim.x + threadIdx.x;
	b[tid] = sin(a[tid]);
}


int main(void) {


	// Solved, Question1, Question2

	/*
	int *d_a, *d_b, *d_c;
	
	int N = 6;
	int size = sizeof(int) * N;

	cudaMalloc((void **)&d_a, size);
	cudaMalloc((void **)&d_b, size);
	cudaMalloc((void **)&d_c, size);
	
	int a[N], b[N], c[N];

	printf("Enter input for A: ");
	for(int i = 0; i < N; i++){
		scanf("%d", &a[i]);
	}
	printf("Enter input for B: ");
	for(int i = 0; i < N; i++){
		scanf("%d", &b[i]);
	}
	
	cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
	
	// add<<<1,1>>>(d_a, d_b, d_c);
	// add1<<<N,1>>>(d_a, d_b, d_c);
	// add2<<<1,N>>>(d_a, d_b, d_c);

	dim3 dimGrid(ceil(N/256.0), 1, 1);
	dim3 dimBlock(256, 1, 1);
	question2<<<dimGrid, dimBlock>>>(d_a, d_b, d_c, N);

	cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
	printf("Result: ");
	for(int i=0; i<N; i++)
		printf("%d ",c[i]);
	printf("\n");

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
	*/


	// Question3

	/*
	float *d_N, *d_M, *d_P;
	
	int l = 6;
	int size = sizeof(float) * l;

	int mask_width = 3;
	float M[] = {1.0,2.0,3.0};
	int maskSize = sizeof(float) * mask_width;

	cudaMalloc((void **)&d_N, size);
	cudaMalloc((void **)&d_M, maskSize);
	cudaMalloc((void **)&d_P, size);
	
	float N[l], P[l];
	printf("Enter input for array N: ");
	for(int i = 0; i < l; i++){
		scanf("%f", &N[i]);
	}
	
	cudaMemcpy(d_N, N, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_M, M, maskSize, cudaMemcpyHostToDevice);
	
	dim3 dimGrid(ceil(l/256.0), 1, 1); // l/256 blocks
	dim3 dimBlock(256, 1, 1);
	question3<<<dimGrid, dimBlock>>>(d_N, d_M, d_P, l, mask_width);

	cudaMemcpy(P, d_P, size, cudaMemcpyDeviceToHost);
	printf("Result: ");
	for(int i=0; i<l; i++)
		printf("%f ",P[i]);
	printf("\n");

	cudaFree(d_N);
	cudaFree(d_M);
	cudaFree(d_P);
	return 0;
	*/

	// Question 4

	int *d_a, *d_b;
	
	int N = 6;
	int size = sizeof(int) * N;

	cudaMalloc((void **)&d_a, size);
	cudaMalloc((void **)&d_b, size);
	
	int a[N], b[N];

	printf("Enter angle in radians: ");
	for(int i = 0; i < N; i++){
		scanf("%d", &a[i]);
	}
	
	cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

	dim3 dimGrid(ceil(N/256.0), 1, 1);
	dim3 dimBlock(256, 1, 1);
	question4<<<dimGrid, dimBlock>>>(d_a, d_b);

	cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost);

	printf("Sin values of given array: ");
	for(int i=0; i<N; i++)
		printf("%d ",b[i]);
	printf("\n");

	cudaFree(d_a);
	cudaFree(d_b);
	return 0;
	
}