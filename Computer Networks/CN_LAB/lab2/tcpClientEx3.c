#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <netdb.h>
#include <arpa/inet.h>
//#include <sys/wait.h>
//#include <signal.h>
 
int main(){
    int sockfd, len, n;
    struct sockaddr_in seraddr, cliaddr;
    char buf_op[2];
    int buf[3];
    int size, pid;

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
    printf("Enter 2 operands\n");
    scanf("%d %d", &buf[0], &buf[1]);
    fflush(stdin);
    printf("Enter an operator\n");
    scanf("%c", &buf_op[0]);

    n = write(sockfd, buf, 2*sizeof(int));
    n = write(sockfd, buf_op, sizeof(char));
    int answer;
    n = read(sockfd, &answer, sizeof(int));
    printf("Solution = %d\n", answer);
    getchar();
    exit(0);
}