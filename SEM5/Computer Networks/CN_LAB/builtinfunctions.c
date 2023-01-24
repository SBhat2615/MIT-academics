#include <stdio.h>
#include <stdlib.h>

int numcmp(int *a, int *b)
{ 
  return(*a - *b);
} 

int main(){
  int arr[] = {4, 2, 5, 6, 3, 9};
  qsort(arr, 6, sizeof(int), numcmp);
  for(int i = 0; i < 6; i++){
    printf("%d ", arr[i]);
  }
}