#include<stdio.h>
#include<stdlib.h>
#include<sys/errno.h>
extern int errno;
int main(){
    int a = 16;
    float b = 9.1;
    char c = 'O';
    char str[] = "Lab 1";
    printf("a=%d \nb=%f \nc=%c \nstr=%s \nscientific = %e \nhexadecimal for a=%x\n",a,b,c,str,b,a);
    errno = EPERM;
    printf("Error Access Errno = %m\n");
}