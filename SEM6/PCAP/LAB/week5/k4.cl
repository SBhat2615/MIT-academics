__kernel void vector_add(__global int* A, __global int* C){
	int i = get_global_id(0);
	
	int n = A[i];
	int remainder;
	int power = 0;
	int number = 0;
	while(n != 0){
		remainder = n % 10;
		n = n/10;
		number += ((2*power)*remainder);
		if(power == 0){
			power = 1;
			number = 1;
		}
		else
			power *= 2;
	}
	C[i] = number;
}