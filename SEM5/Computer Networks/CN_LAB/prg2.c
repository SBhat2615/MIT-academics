// Client

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
  
  struct sockaddr_in cliaddr;
  int sockfd, newsockfd, len, n, result;

  // socket desc
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  cliaddr.sin_family = AF_INET;
  cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  cliaddr.sin_port = htons(PORTNO);

  len = sizeof(cliaddr);
  // connect client socket to server socket
  result = connect(sockfd, (struct sockaddr_in* )&cliaddr, len);

  while(n){
    char buf[256], ch[256];
    // Communicate with server
    printf("Enter string: ");
    scanf("%s", ch);

    // write to server
    ch[strlen(ch)] = '\0';
    write(sockfd, ch, sizeof(ch));

    // read from server
    n = read(sockfd, buf, sizeof(buf));
    buf[n] = '\0';
    puts(buf);
  }
  close(sockfd);
}