#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MYPORT "3490"
#define BACKLOG 10

int		main(void)
{
	struct sockaddr_storage		their_addr;
	socklen_t					addr_size;
	struct addrinfo				hints;
	struct addrinfo				*res;
	int							sockfd, new_fd;

	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	// make a socket, bind it, and listen on it

	getaddrinfo(NULL, MYPORT, &hints, &res);
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	bind(sockfd, res->ai_addr, res->ai_addrlen);
	listen(sockfd, BACKLOG);

	addr_size = sizeof(their_addr);
	new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &addr_size);

	// ready to communicate on socket descripter new_fd
}
