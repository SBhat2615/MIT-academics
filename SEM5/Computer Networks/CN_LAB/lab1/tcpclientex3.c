#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    struct tm* timeinfo;
    char* reply;
    int hour,mins,sec,pid;

    /*  Create a socket for the client.  */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /*  Name the socket, as agreed with the server.  */

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = 8000;

    /*  Now connect our socket to the server's socket.  */

    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) 
    {
        perror("Connection failed\n");
        exit(1);
    }

    /*  We can now read/write via sockfd.  */
   
    printf("Request sent to time server to send current time\n");
    
    read(sockfd, &hour , 1);
    read(sockfd, &mins , 1);
    read(sockfd, &sec , 1);
    read(sockfd, &pid , 1);
    printf("Time: %d:%d:%d\n", hour, mins, sec);
    printf("The process id is: %d\n",pid);

    close(sockfd);
    exit(0);
}
