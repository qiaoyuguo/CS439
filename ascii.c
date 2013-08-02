#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

// Prototype of functions that you will be implementing.
int generate_ascii(char *output_file, int rows, int cols);
int fibonacci_ascii(char *file_in, char *file_out);

int
main(int argc, char **argv)
{
	int num_rows, num_cols;

	if (argc < 5) {
		printf("Usage: %s num_row num_col output_file1 output_file2\n", argv[0]);
		return -1;
	}

	num_rows = atoi(argv[1]);
	num_cols = atoi(argv[2]);	

	if (generate_ascii(argv[3], num_rows, num_cols) < 0)
		return -1;
 
	return fibonacci_ascii(argv[3], argv[4]);
}

// Generate ASCII art using random bytes from /dev/urandom.
//	The dimensions should be rows x cols.
// Use only values between 33 and 126 (see the decimal set in man ascii
//	for more information). 
//
// You do not have to worry about reading or writing more than one character
// in a single syscall.
//
// Print an error and return -1 if any I/O operations fail.  If everything
// goes successfully, return 0.
int
generate_ascii(char *output_file, int rows, int cols)
{
        int i = 0,j = 0;
	int rand_fd, out_fd;
	int c;
	int ret;
	int rc;

        rand_fd = open("/dev/urandom", O_RDONLY | O_TRUNC | O_CREAT, 0600);
        if(rand_fd  < 0)
        {
            fprintf(stderr, "Could't open %s, Error: %s\n", "dev/urandom", strerror(errno));
            return -1;
        }
        if((out_fd = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0600)) < 0)
        {
            fprintf(stderr, "Could't open %s, Error: %s\n", output_file, strerror(errno));
            return -1;
        }
        do
        {
            if(j == cols)
            {
                c = '\n';
                rc = write(out_fd, &c, 1);
                if(rc == -1)
                {
                    fprintf(stderr, "Could't write to %s, Error: %s\n", output_file, strerror(errno));
                    return -1;
                }
                ++i;
                if(i == cols)
                    break;
                j = 0;
            }
           ret = read(rand_fd, &c, 1);
            if(ret == -1)
            {

                fprintf(stderr, "Could't read from %s, Error: %s\n", "/dev/urandom", strerror(errno));
                return -1;
            }
            if(c >= 33 && c <= 126)
            {
                rc = write(out_fd, &c, 1);
                if(rc == -1)
                {
                    fprintf(stderr, "Could't write to %s, Error: %s\n", output_file, strerror(errno));
                    return -1;
                }
                ++j;
            }

        }while(ret > 0 && i < rows);

	close(rand_fd);
	close(out_fd);

	return 0;
}


// fibonacci_ascii: writes into file_out the ascii values from file_in that
// fall in fibonacci indexes.  This includes any newline characters.
//
// Recall that the fibonacci sequence is: 0, 1, 1, 2, 3, 5, ...
// You need to copy the 0th, 1st, 1st, 2nd, ... ascii value from file_in
// into file_out, until you reach the end of file_in. 
//
// Note that the first byte of a file is the byte at position 0.
//
// Example:
//
//  The contents of the file 'file_in' are:  a-{}""${}@::$#
//  The file 'file_out' should contain: a--{"$@
//
// Requirements:
// You cannot read and store the entire contents of file_in into memory.
// You may only read 1 byte at a time.
//
// Print an error and return -1 if any I/O operations fail.  If everything
// goes successfully, return 0.
//
// Hint: You may find the lseek system call helpful here.
int
fibonacci_ascii(char *file_in, char *file_out)
{
	int in_fd, out_fd;
	ssize_t rc;
	int first = 1;
	int fib1 = 0, fib2 = 1, pos;
	int c;
	int ret;

        if( (in_fd = open(file_in, O_RDONLY)) < 0)
        {
            fprintf(stderr, "Could't open %s, Error: %s\n", file_in, strerror(errno));
            return -1;
        }

	if((out_fd = open(file_out, O_WRONLY | O_TRUNC | O_CREAT, 0600)) < 0)
        {
            fprintf(stderr, "Could't open %s, Error: %s\n", file_in, strerror(errno));
            return -1;
        }

        do
        {
            
            if(first)
            {
                pos = fib1;
                first = 0;
            }
            else
            {
                int tmp;
                pos = fib2;
                tmp = fib2;
                fib2 += fib1;
                fib1 = tmp;
            }
            ret = lseek(in_fd, pos, SEEK_SET);
            if(ret < 0)
            {
                break;
                //fprintf(stderr, "Could't seek  position %d in file %s, Error: %s\n",pos,  "/dev/urandom", strerror(errno));
                //return -1;
            }
            rc = read(in_fd, &c, 1);
            if(rc < 0)
            {
                fprintf(stderr, "Could't read from file %s, Error: %s\n",  file_in, strerror(errno));
                return -1;
            }
            else if(rc == 0)
            {
                c = '\n';
            }
            int rt = write(out_fd, &c, 1);
            if(rt == -1)
            {
                fprintf(stderr, "Could't write %s, Error: %s\n", file_in, strerror(errno));
            }
        }while(rc > 0);

        close(in_fd);
        close(out_fd);

        return 0;
}
