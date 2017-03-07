#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMELTS 16384
#define IN 0
#define OUT 1

// IMPORTANT: Compile using "gcc assg2p2.c .lm -o assg2p2".
// The "-lm" is important as it brings in the Math library.

// Implements the naive primality test.
// Returns TRUE if n is a prime number
int prime(int n) {
    int ret = -1, i;

    for (i = 2; i <= (int) sqrt(n) && ret; i++) {
        ret = n % i;
    }
    return ret;
}

/**
 * Counts the number of prime numbers in an array
 * 
 * @param startIdx starting index of the array.
 * @param lenToRead sizeof the array to look at.
 * @return count of prime numbers in the list.
 */
int primeCounter(int *numbers, int startIdx, int lenToRead) {
    int count = 0, i;
    for (i = startIdx; i < lenToRead; i++) {
        if (prime(numbers[i])) {
            count += 1;
        }
    }
    return count;
}

/**
 * Parent will print out the total prime count including the child's count.
 *
 * @param fd controls the pipe for parent to read child number.
 * @param data contains data to be analysed for prime.
 */ 
void parentPrintOutTotalPrimeCount(int *fd, int *data) {
    int cnum = 0;
    close(fd[OUT]);
    int primeCounts = primeCounter(data, 0, (NUMELTS/2));
    read(fd[IN], &cnum, sizeof(cnum));
    close(fd[IN]);

    primeCounts += cnum;

    printf("Total prime count = %d\n", primeCounts);
}

/**
 * Child will send the parent its prime count.
 *
 * @param fd controls the pipe for child to send to parent.
 * @param data contains data to be analysed for prime.
 */
void childSendParentPrimeCount(int *fd, int *data) {
    close(fd[IN]);
    int primeCounts = primeCounter(data, NUMELTS/2, NUMELTS);
    write(fd[OUT], &primeCounts, sizeof(primeCounts));
    close(fd[OUT]);
}

int main() {
    int data[NUMELTS], i;
    srand(time(NULL));
    pid_t pid = -1;

    // Declare other variables here.
    int fd[2];

    if (pipe(fd) == -1) {
        perror("Unable to pipe properly\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < NUMELTS; i++) {
        data[i] = (int) (((double) rand() / (double) RAND_MAX) * 10000);
    }

    pid = fork();
    if (pid > 0) {
        parentPrintOutTotalPrimeCount(fd, data);
    } else if (pid == 0) {
        childSendParentPrimeCount(fd, data);
    } else {
        perror("Unable to fork");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
