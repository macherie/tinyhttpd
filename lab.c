#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>


int main(int argc, const char *argv[])
{
	
	int server_fd, client_fd;

	struct sockaddr_in myaddr;
	struct sockaddr_in client_addr;
	int client_len = sizeof(client_addr);
	char content[] = "<html><h1>hello xin.qi@sim.com</h1></html>";

	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(8089);

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
		perror("server_fd error");
	if (bind(server_fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1)
		perror("bind error");
	
	if (listen(server_fd, 10) == -1)
		perror("listen error");

	while (1) {
		printf("accept \n");
		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
		send(client_fd, content, sizeof(content), 0);
	}

	return 0;
}
