#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define NUMELTS 16384
// IMPORTANT: Compile using "gcc assg2p2.c .lm -o assg2p2".
// The "-lm" is important as it brings in the Math library.
// Implements the naive primality test.
// Returns TRUE if n is a prime number
int prime(int n)
{
int ret=1, i;
for(i=2; i<=(int) sqrt(n) && ret; i++)
ret=n % i;
return ret;
}
int main()
{
int data[NUMELTS];
// Declare other variables here.
// Create the random number list.
srand(time(NULL));
for(i=0; i<NUMELTS; i++)
data[i]=(int) (((double) rand() / (double) RAND_MAX) * 10000);
// Now create a parent and child process.
//PARENT:
// Check the 0 to 8191 sub-list
// Then wait for the prime number count from the child.
// Parent should then print out the number of primes
// found by it, number of primes found by the child,
// And the total number of primes found.
// CHILD:
// Check the 8192 to 16383 sub-list.
// Send # of primes found to the parent.
}