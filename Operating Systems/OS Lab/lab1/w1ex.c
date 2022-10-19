#include<unistd.h>
#include<stdlib.h>
int main(){
	if((write(1,"Data\n",5)) != 5)
	write(2,"Write error has occurred on file descriptor 1\n", 44);
	exit(0);
}
