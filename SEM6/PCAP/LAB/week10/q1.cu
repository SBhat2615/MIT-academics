#include <stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void sparse1(int num_rows, float* data, int* col_index, int* row_ptr, float* x, float* y){
	
	int row = blockIdx.x * blockDim.x + threadIdx.x;
	if(row < num_rows){
		// perform multiplication
	}
}

int main(void){
	int *d_a;
	int *data, *col_index, *row_ptr;
	int A[20][20], m, n;
	int B[m];

	printf("Enter size of matrix: ");
	scanf("%d%d", &m, &n);

	int size = m*n*sizeof(int);

	data = (int*)malloc(size);
	col_index = (int*)malloc(size);
	row_ptr = (int*)malloc((m+1)*sizeof(int));

	printf("Enter the elements for Matrix: ");
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++)
			scanf("%d", &A[i][j]);
	}

	printf("Enter the elements for Vector: ");
	for(int i = 0; i < m; i++){
		scanf("%d", &B[i]);
	}

	// Convert to Sparse
	int k = 0, l = 0;
	for(int i = 0; i < m; i++){
		int flag = 1;
		for(int j = 0; j < n; j++){
			if(A[i][j] != 0){
				data[k] = A[i][j];
				col_index[k] = j;
				if(flag){
					row_ptr[l++] = k;
					flag = 0;
				}
				k++;
			}
		}
	}

	/*
	printf("Sparse Matrix:\n");
	for(int i = 0; i < k; i++){
		printf("%d - %d\n", data[i], col_index[i]);
	}

	for(int i = 0; i < l; i++){
		printf("%d ", row_ptr[i]);
	}
	*/

	size1 = (k-1)*sizeof(int);
	size2 = m*sizeof(int);
	cudaMalloc((void**)&d_a, size1);
	cudaMalloc((void**)&d_b, size2);

	cudaMemcpy(d_a, a, size1, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, size2, cudaMemcpyHostToDevice);
	// cudaMemcpy for other kernel arguments(pointer args)

	// CALL KERNEL FUNCTION

	getchar();
	return 0;
}