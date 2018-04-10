#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdlib.h>
#include <time.h>

int socket_connect(char *host, in_port_t port){
	struct hostent *hp;
	struct sockaddr_in addr;
	int on = 1, sock;     

	if((hp = gethostbyname(host)) == NULL){
		herror("gethostbyname");
		exit(1);
	}
	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));

	if(sock == -1){
		perror("setsockopt");
		return -1;
		//exit(1);
	}
	
	if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
		perror("connect");
		return -1;
		//exit(1);

	}
	return sock;
}
 
#define BUFFER_SIZE 100

int main(int argc, char *argv[]){
        srand(time(NULL)); 

	if(argc < 2){
		fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
		exit(1); 
	}
	
	int j;
	for (j=0; j<1000; j++) {
		int fd;
		char buffer[BUFFER_SIZE];
	
		fd = socket_connect(argv[1], atoi(argv[2])); 
		if (fd == -1) {
			fprintf(stdout, "no more sockets, got -1");
			continue;
		}
	        int length=12*1024*1024;
		char *input = malloc(length);
		int i,n;
		for (i = 0; i < length; ) {
			n = rand() % 26 + 'a';
			input[i++] = n;
	        }
		input[length - 1] = 0;    
	
		write(fd, input, strlen(input)); // write(fd, char[]*, len);  
		bzero(buffer, BUFFER_SIZE);
	        free(input);
		fprintf(stdout, "%d\n", j);
		
		read(fd, buffer, BUFFER_SIZE - 1);
		shutdown(fd, SHUT_RDWR); 
	}

	sleep(6000);
	return 0;
}
