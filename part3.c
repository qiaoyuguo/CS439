#include <stddef.h>
#include <assert.h>

// Return the sum of all elements in the given array.  The array
// "arr" has "n" elements.
//
// Note that before, we used pointers to reference single variables
// in memory, but now we are using them to refer to many elements.
// The "arr" pointer points to the first element in the array in memory.
// Because pointers themselves don't carry any length information
// (like array objects do in Java), we generally have to pass in a
// length parameter to functions which use pointers to reference
// arrays.
int
array_sum(int *arr, int n)
{
        int i;
	int sum = 0;
	for(i = 0; i < n; i++)
	    sum += arr[i];
	return sum;
}
