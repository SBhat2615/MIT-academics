#include <unistd.h>
#include <stdlib.h>

int main(){
	char buffer[128];
	int nread;
	nread = read(0, buffer, 128);				//read
	if(nread == -1)						//try with single =
		write(2,"A read error has occurred\n",26);
	if((write(1,buffer,nread)) != nread)			//try with == instead of != 
		write(1,"A write error has occurred\n",27);	//what's the diff. btw 1 & 2
	exit(0);
}
