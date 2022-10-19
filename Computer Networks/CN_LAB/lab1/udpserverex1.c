#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 5000
#define MAXLINE 1000

// Server code
int main()
{
	int buffer[100];
	int servsockfd, len,n;
	struct sockaddr_in servaddr, cliaddr;
	bzero(&servaddr, sizeof(servaddr));

	// Create a UDP Socket
	servsockfd = socket(AF_INET, SOCK_DGRAM, 0);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	// bind server address to socket descriptor
	bind(servsockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	//receive the datagram
	len = sizeof(cliaddr);
	n = recvfrom(servsockfd, buffer, sizeof(buffer),0, (struct sockaddr*)&cliaddr,&len);
	buffer[n] = '\0';

	int r, c;
	printf("Enter number of row and columns: ");
	scanf("%d %d", &r, &c);

	int k = 0;
	printf("Array is:\n");
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			printf("%d ", buffer[k]);
			k++;
		}
		printf("\n");
	}

	//Echoing back to the client
	sendto(servsockfd, buffer, n, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
	getchar();

	// close the descriptor
	close(servsockfd);
}
