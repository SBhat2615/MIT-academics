#include<stdio.h>
#include<stdlib.h>
int main(){
    char* mem = (char*)malloc(1024);
    if(mem) printf("Memory successfully allocated\n");
    else printf("Memory allocation failed.");
    mem  = realloc(mem, 0);
    if(!mem) printf("Memory successfully released\n");
    else printf("Memory release failed.");
    mem  = realloc(mem, 2048);
    if(mem) printf("Memory successfully reallocated\n");
    else printf("Memory reallocation failed.");
    int h[100];
    free(mem);
    printf("Memory freed.");
    return 0;
}