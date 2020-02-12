#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Gets the highest common factor of two numbers.
 * @param x
 * @param y
 * @return
 */
long greatest_common_factor(int32_t x, int32_t y) {
    uint32_t temp;
    while (y != 0) {
        temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}


/**
 * Checks if parameter x and y are relatively prime.
 * @return True if prime
 */
bool relatively_prime(uint32_t x, uint32_t y) {
    return greatest_common_factor(x, y) == 1;
}

/**
 * Calculates the euler totient.
 *
 * Gets the number of positive integers smaller
 * than n and relatively prime to n.
 */
uint32_t euler_totient(uint32_t n) {
    uint32_t length = 0;
    for (uint32_t i = 1; i < n; i++)
        if (relatively_prime(n, i))
            length++;
    return length;
}

/**
 * Returns the sum of all the euler_totients
 * between lower and upper.
 */
uint32_t sum_totient(uint32_t lower, uint32_t upper) {
    uint32_t sum = 0;
    for (uint32_t i = lower; i <= upper; i++)
        sum = sum + euler_totient(i);
    return sum;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "error: must provide lower and upper bounds\n");
        printf("usage: totient LOWER UPPER\n");
        return 1;
    }
    uint32_t lower = strtoul(argv[1], NULL, 10);
    uint32_t upper = strtoul(argv[2], NULL, 10);
    printf("%u\n", sum_totient(lower, upper));
}
