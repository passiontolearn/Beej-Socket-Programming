/*
**  Blocking is a term for "sleep", where a function does nothing until data arrives.
**
**  To make a socket non-blocking you have to make a call to fcntl(). This allows you
**  to poll the socket for information. If there is no data on a non-blocking socket,
**  it returns -1 and the errno is set to EAGAIN or EWOULDBLOCK.
*/

/*
**  How to turn off blocking
*/

#include <unistd.h>
#include <fcntl.h>

sockfd = socket(PF_INET, SOCK_STREAM, 0);
fcntl(sockfd, F_SETFL, O_NONBLOCK);

/*
**  The select() function allows you to monitor several sockets simultaneously, telling
**  you which ones are ready for reading, which are ready for writing, and which sockets
**  have raised exceptions
*/

// Brief synopsis of select()

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int     select(int numfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
                    struct timeval *timeout);

/*
** The following macros operate on the type fd_set
*/

FD_SET(int fd, fd_set *set);    // Add fd to the set
FD_CLR(int fd, fd_set *set);    // Remove fd from the set
FD_ISSET(int fd, fd_set *set);  // Return true if fd is in the set
FD_ZERO(fd_set *set);           // Clear all entries from the set

/*
** The timeval structure
*/

struct timeval {
    int     tv_sec;     // seconds
    int     tv_usec;    // microseconds
}

// if the fields in timeval are set to 0, select() effectively polls fds in the sets
// if you set the parameter timeout to NULL, select() will never time out

/*
**  Furthermore, if a socket closes when you use select() the function will return it
**  as ready for reading. When you use revc(), it will return 0, meaning the socket
**  has closed.
*/

/*
**  There are three ways to send binary data (ints, floats) across the network
**      1. Convert the number into text with a function like snprintf and send it.
**         The receiver will parse the text back into a number
**      2. Send the data raw by passing a void pointer.
**      3. Encode the number into a portable binary form and the receiver will
**         decode it.
**
**  The advantage of #1 is that it is easy to print/read data coming over the wire.
**  The disadvantage of #1 is that it is slow to convert and the results usually
**  take up more space than the original number.
**
**  The advantage of #2 is that it is very simple to implement, however the issue
**  is that the bit representation of integral data types depends on architecture.
**
*/

/*
**  Since the compiler is free to put padding anywhere inside a struct, we cannot
**  portably send structs over the wire in one chunk. We have to pack each field
**  independently and unpack them into the struct when they arrive on the other side
*/

