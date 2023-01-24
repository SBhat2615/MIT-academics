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
 
int main(){
    int sockfd, len, n, size;
    struct sockaddr_in seraddr, cliaddr;
    int buf[256];
    int pid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
		printf("Error in creating socket");
        exit(1);
	}
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = INADDR_ANY;
    seraddr.sin_port = htons(10200);
    len = sizeof(seraddr);
    connect(sockfd, (struct sockaddr *)&seraddr, len);

    printf("Enter number of elements:\n");
    scanf("%d", &size);
    printf("Enter elements:\n");

    for(int i = 0; i < size; i++){
      scanf("%d", &buf[i]);
    }

    n = write(sockfd, &size, sizeof(int));
    n = write(sockfd, buf, size*sizeof(int));
    
    n = read(sockfd, &pid, sizeof(int));
    n = read(sockfd, buf, size*sizeof(int));  //size * sizeof(int) bcz buf size is 256 {sizeof(buf) not possible}
    printf("\nArray after sorting: ");
    for(int i = 0; i < size; i++){
        printf("%d ", buf[i]);
    }
    printf("\nProcess ID: %d\n", pid);
    getchar();
}