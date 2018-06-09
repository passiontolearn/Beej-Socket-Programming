#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int		getaddrinfo(const char *node,		// "www.example.com" or IP
				const char *service,	// "http" or port number
				const struct addrinfo *hints,
				struct addrinfo **res);

// sample call if you're a server who wants to listen on your host's IP address, port 3490

int					status;
struct addrinfo		hints;
struct addrinfo		*servinfo;	// will point to the results

memset(&hints, 0, sizeof(hints));
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;	// tcp stream sockets
hints.ai_flags = AI_PASSIVE;		// fill in my IP for me

if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)))
{
	fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
	exit(1);
}

//  servinfo now points to a linked list of 1 or more struct addrinfos

//  ... do everything until you don't need servinfo anymore

freeaddrinfo(servinfo);

// sample call if you're a client who wants to connect to a particular server on port 3490

int					status;
struct addrinfo		hints;
struct addrinfo		*servinfo;

memset(&hints, 0, sizeof(hints));
hints.ai_family =  AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;

//  get ready to connect
status = getaddrinfo("www.example.net", "3490", &hints, &servinfo);

//  servinfo now points to a linked list of 1 or more struct addrinfos

int		socket(int domain, int type, int protocol);	// returns a socket descriptor

int		s;
struct addrinfo hints, *res;

// do the lookup
getaddrinfo("www.example.com", "http", &hints, &res);

s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

//  Once you have a socket you might have to associate that socket with a port on your local machine
//  This is commonly done if you want to use listen() for incoming connections on a specific port

int		bind(int sockfd, struct sockaddr *my_addr, int addrlen);

//  Here is an example that binds the socket to the host the program is running on

int		sockfd;

bzero(&hints, sizeof(hints));
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;
hints.ai_flags = AI_PASSIVE;

getaddrinfo(NULL, "3490", &hints, &res);

sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

bind(sockfd, res->ai_addr, res->ai_addrlen);

int		connect(int sockfd, struct sockaddr *serv_addr, int addrlen);

//  Here's an example where we make a socket connection to www.example.com

int				sockfd;
struct addrinfo hints, *res;

bzero(&hints, sizeof(hints));
hints.ai_family(AF_UNSPEC);
hints.ai_socktype = SOCK_STREAM;

getaddrinfo("www.example.com", "3490", &hints, &res);

sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

connect(sockfd, res->ai_addr, res->ai_addrlen);

// Notice we didn't call bind, since the kernel will choose a local port
// for us and the site we connect to will automatically get this from us

//  What do you do when you want to wait for incoming connections and
//  handle them some way? The process is shown below

int		listen(int sockfd, int backlog);	// backlog is the number of connections allowed in the queue

//  Need to call bind() so that the server can run on a specific port

getaddrinfo();
socket();
bind();
listen();
//  accept() goes here

//  When you accept a client connection, the syscall returns a new socket file descriptor for send()
//  and recv()

int		accept(int sockfd,	// The listening socket descriptor
				struct sockaddr *addr,  // Where info about the incoming connection is stored
					socklen_t *addrlen); // Local int variable

int		send(int sockfd, const void *msg, int len, int flags);  // For our purposes, set flags to 0

// Send returns the number of bytes sent out. If this is less than what you've specified, it assumes
// that you will send out the rest yourself.

int		recv(int sockfd, void *buf, int len, int flags);  // For our purposes, set flags to 0

// Recv returns the nubmer of bytes read into the buffer and -1 on error. If recv returns 0, it means
//  that the server has closed the connection.

close(sockfd); // Prevents any more read or writes to the socket. Any attempts will return an error.

int		shutdown(int sockfd, int how);  // how = 0 means further receives are disallowed
										// how = 1 means further sends are disallowed
										// how = 2 means further sends/receives are disallowed
										// Note: shutdown does NOT free the socket, it simply changes its
										// usage.
