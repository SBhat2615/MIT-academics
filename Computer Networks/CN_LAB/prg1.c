// Server

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORTNO 10200

int main(){
  
  struct sockaddr_in servaddr, cliaddr;
  int sockfd, newsockfd, len, clilen, n;

  // socket desc
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORTNO);

  // bind socket desc to server address
  len = sizeof(servaddr);
  bind(sockfd, (struct sockaddr_in* )&servaddr, len);
  listen(sockfd, 5);

  // waiting for client
  printf("Server Waiting\n");
  clilen = sizeof(cliaddr);

  // get client socket desc
  newsockfd = accept(sockfd, (struct sockaddr_in*)&cliaddr, &clilen);
  while(1){
    char buff[256];
    n = read(newsockfd, buff, sizeof(buff));
    printf("Client message : %s\n", buff);
    n = write(newsockfd, buff, sizeof(buff));
  }
  close(sockfd);
}