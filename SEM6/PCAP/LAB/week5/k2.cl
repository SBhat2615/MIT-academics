__kernel void vector_add(__global int* A, __global int* C){
	int i = get_global_id(0);
	
	int n = A[i];
	int count = 0;
	
	while(n != 0){
		n = n >> 1;
		count += 1;
	}
	
	n = 1 << count;
	C[i] = n - 1 - A[i];
}