/*
**  Structures
*/

struct addrinfo {
    int     ai_flags;
    int     ai_family;  // Use this to force IPv4, IPv6, or leave unspec
    int     ai_socktype;    //SOCK_STREAM, SOCK_DGRAM
    int     ai_protocol;    // Use 0 for "any protocol"
    size_t  ai_addrlen;
    struct sockaddr *ai_addr;
    char    ai_cannonname;
    struct addrinfo *ai_next;   // linked list, next node
}

struct sockaddr {
    unsigned short  sa_family;  // address family, AF_xxxx
    char            sa_data[14];
}

// IPv4 only -- see struct sockaddr_in16 for IPv6
struct sockaddr_in {
    short int           sin_family;
    unsigned short int  sin_port;
    struct in_addr      sin_addr;
    unsigned char       sin_zero[8];
}

struct in_addr {
    uint32_t    s_addr;
}

// IPv6 only -- see sockaddr_in for IPv4
struct sockaddr_in6 {
    u_int16_t   sin6_family;
    u_int16_t   sin6_port;
    u_int32_t   sin6_flowinfo;
    struct in16_addr    sin6_addr;
    u_int32_t   sin6_scope_id;
}