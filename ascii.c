#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// Prototype of functions that you will be implementing.
int generate_ascii(char *output_file, int rows, int cols);
int fibonacci_ascii(char *file_in, char *file_out, int rows, int cols);

int
main(int argc, char **argv)
{
	int num_rows, num_cols;

	if (argc < 5) {
		printf("Usage: %s num_row num_col output_file1, output_file2\n", argv[0]);
		return -1;
	}

	num_rows = atoi(argv[1]);
	num_cols = atoi(argv[2]);	

	if (generate_ascii(argv[3], num_rows, num_cols) < 0)
		return -1;
 
	return fibonacci_ascii(argv[3], argv[4], num_rows, num_cols);
}

// Generate ASCII art using random bytes from /dev/urandom.
//	The dimensions should be rows x cols.
// Use only values between 33 and 126 (see the decimal set in man ascii
//	for more information). 
//
// Print an error and return -1 if any I/O operations fail.  If everything
// goes successfully, return 0.
int
generate_ascii(char *output_file, int rows, int cols)
{
	int rand_fd, out_fd;

	//TODO: Your code goes here.
	printf("Error: generate_ascii not implemented\n");
	return -1;
}


// fibonacci_ascii: writes into file_out the ascii values from file_in that
// fall in fibonacci indexes.
// 
// Recall that the fibonacci sequence is: 0, 1, 1, 2, 3, 5, ...
// You need to copy the 0th, 1st, 1st, 2nd, ... ascii value from file_in
// into file_out, until you reach the end of file_in. 
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
int
fibonacci_ascii(char *file_in, char *file_out, int rows, int cols)
{
	int in_fd, out_fd;

	//TODO: Your code here.
	printf("Error: fibonacci_ascii not implemented\n");
	return -1;
}
