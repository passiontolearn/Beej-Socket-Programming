#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int     main(void)
{
    char            buf[32];
    int             bytes_read;
    struct timeval  tv;
    fd_set          readfds;

    tv.tv_sec = 2;
    tv.tv_usec = 250000;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    printf("STDIN added to the fd_set\n");

    select(STDIN_FILENO, &readfds, NULL, NULL, &tv);
    if (FD_ISSET(STDIN_FILENO, &readfds))
    {
        bytes_read = read(STDIN_FILENO, &buf, 32);
        printf("sucess: read %d bytes from stdin:\n%s", bytes_read, buf);
    }
    else
        printf("time out: no data read\n");
    return (0);
}