/*
 * =====================================================================================
 *
 *       Filename:  hi.c
 *
 *    Description:  a small sample program explaining usage of open and close function
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int
main(int argc, char **argv)
{
	int fd;
	if ( (fd = open("hi.txt", O_WRONLY|O_TRUNC|O_CREAT, 0600)) < 0)
        {
            fprintf(stderr, "Couldn't open hi.txt. Error: %s\n",
                    strerror(errno));
            return -1;
        }

	write(fd, "hello, world\n", 13);
	close(fd);
	return 0;
}
