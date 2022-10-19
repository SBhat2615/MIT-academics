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

int calc(int a, int b, char c){
    switch(c){
        case '+':
            return a + b;
            break;
        case '-':
            return a - b;
            break;
        case '/':
            return a / b;
            break;
        case '*':
            return a * b;
            break;
        default:
            return 0;
            break;
    }
}
int main(){
    int sockfd, newsockfd, len, n, size;
    struct sockaddr_in seraddress, cliaddr; 
    int buf[3];
    char buf_op[2];
    printf("Initiating server\n");
    sockfd=socket(AF_INET, SOCK_STREAM, 0); 
    if(sockfd == -1){
		    printf("Error in creating socket");
        exit(1);
	  }
    seraddress.sin_family=AF_INET; 
    seraddress.sin_addr.s_addr=INADDR_ANY; 
    seraddress.sin_port=htons(10200); 

    bind(sockfd,(struct sockaddr*)&seraddress,sizeof(seraddress)); 

    listen(sockfd,5); 
    len=sizeof(cliaddr); 

    while(1){
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
        puts("Connection to client established\n");

        if(fork() == 0){
            // child process, only concerned with data transfer
            close(sockfd);
            n = read(newsockfd, buf, 2*sizeof(int));  // read integers
            n = read(newsockfd, buf_op, sizeof(char));
            printf("Operation to be performed = %d %c %d", buf[0], buf_op[0], buf[1]);
            int answer = calc(buf[0], buf[1], buf_op[0]);
            n = write(newsockfd, &answer, sizeof(int));

            getchar();    
            close(newsockfd);
        }
    }
    exit(0);
}