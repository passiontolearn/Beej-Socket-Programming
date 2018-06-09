#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int		main(int ac, char **av)
{
	int					status;
	char				ipstr[INET6_ADDRSTRLEN];
	struct addrinfo		hints, *res, *p;

	if (ac == 2)
	{
		bzero(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		if ((status = getaddrinfo(av[1], NULL, &hints, &res)))
		{
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
			return (2);
		}
		
		printf("IP addresses for %s:\n\n", av[1]);

		for (p = res; p != NULL; p = p->ai_next)
		{
			void	*addr;
			char	*ipver;

			// get the pointer ot the address itself,
			//  different fields in IPv4 and IPv6
			if (p->ai_family == AF_INET)
			{
				struct sockaddr_in  *ipv4 = (struct sockaddr_in*)p->ai_addr;
				addr = &(ipv4->sin_addr);
				ipver = "IPv4";
			}
			else
			{
				struct sockaddr_in6 *ipv6 = (struct sockaddr_in6*)p->ai_addr;
				addr = &(ipv6->sin6_addr);
				ipver = "IPv6";
			}

			//  convert the IP to a string and print it:
			inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
			printf(" %s: %s\n", ipver, ipstr);
		}
		freeaddrinfo(res);	// free the linked list
		return (0);
	}
}
