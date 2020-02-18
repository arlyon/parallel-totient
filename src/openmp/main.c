#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common.h"

/**
 * Returns the sum of all the euler_totients
 * between lower and upper.
 */
uint32_t sum_totient(uint32_t lower, uint32_t upper)
{
    uint32_t sum = 0;
    for (uint32_t i = lower; i <= upper; i++)
        sum = sum + euler_totient(i);
    return sum;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "error: must provide lower and upper bounds\n");
        printf("usage: totient LOWER UPPER\n");
        return 1;
    }
    uint32_t lower = strtoul(argv[1], NULL, 10);
    uint32_t upper = strtoul(argv[2], NULL, 10);
    printf("%u\n", sum_totient(lower, upper));
}
