#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <arpa/inet.h> 
#include <sys/wait.h> 
#include <signal.h> 


void sort(int arr[],int n){
	for(int i =0;i<n-1;i++){
		for(int j = 0;j<n-i-1;j++){
			if(arr[j] > arr[j+1]){
				int temp=arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int main(){
    int sockfd, newsockfd, clilen, n, size;
    struct sockaddr_in seraddr, cliaddr;
    int buf[256];
    
    printf("Initiating server\n");
    sockfd=socket(AF_INET, SOCK_STREAM, 0); 
    if(sockfd == -1){
		printf("Error in creating socket");
        exit(1);
	}
    seraddr.sin_family=AF_INET; 
    seraddr.sin_addr.s_addr=INADDR_ANY; 
    seraddr.sin_port=htons(10200); 

    bind(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr)); 

    listen(sockfd,5); 
    clilen=sizeof(cliaddr); 

    while(1){
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        puts("Connection to client established\n");

        if(fork() == 0){
            // child process, only concerned with data transfer
            close(sockfd);
            int pid = getpid();
            n = read(newsockfd, &size, sizeof(int));        // reads size to size variable
            n = read(newsockfd, buf, size*sizeof(int));// size required here ; //size * sizeof(int) bcz buf size is 256 {sizeof(buf) not possible}
            printf("Array sent from client:\n");
            for(int i =0; i<size; i++){
            	printf("%d ",buf[i]);
            }
            sort(buf, size);
            //printf("\nProcess ID:%d",pid);
            // Write pid & array buffer
            n = write(newsockfd, &pid, sizeof(int));
            n = write(newsockfd, buf, size*sizeof(int));
            getchar();    
            close(newsockfd);
        }
    }
}