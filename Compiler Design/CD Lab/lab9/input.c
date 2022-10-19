#include<stdio.h>
#include<stdlib.h>
main(){
  int a[15];
  int p, q, r, s;
  p = q+r%s;
  if(q){
    p = q;
  }
  else{
    q = p;
  }
  for(i=1;p+q;i=i+1){
    p = p+i;
  }
  while(i<5){
    q = q+i;
  }
}