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
	int rand_fd, out_fd;

	//TODO: Your code goes here.
	fprintf(stderr, "Error: generate_ascii not implemented\n");
	return -1;
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

	//TODO: Your code here.
	fprintf(stderr, "Error: fibonacci_ascii not implemented\n");
	return -1;
}
