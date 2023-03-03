__kernel void vector_add(__global int* A, __global int* B, __global int* C){
	int i = get_global_id(0);
	
	int remainder = 0;
	int octal = 0, power = 1;

	while(A[i] != 0){
		remainder = A[i] % 8;
		A[i] = (int)A[i]/8;
		C[i] += (remainder*power);
		power *= 10;
	}
}