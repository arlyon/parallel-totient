// TotientRance.c - Sequential Euler Totient Function (C Version)
// compile: gcc -Wall -O -o TotientRange TotientRange.c
// run:     ./TotientRange lower_num uppper_num

// Greg Michaelson 14/10/2003
// Patrick Maier   29/01/2010 [enforced ANSI C compliance]

// This program calculates the sum of the totients between a lower and an
// upper limit using C longs. It is based on earlier work by:
// Phil Trinder, Nathan Charles, Hans-Wolfgang Loidl and Colin Runciman

#include <stdio.h>
#include <time.h>
// Added By Jerome
#include <stdint.h>
#include <stdbool.h>
#include "common.h"
#include "cli.h"

// Jerome removed common functions from "common.h"
// Replaced long by uint32_t to bring in line with rest of project


// sumTotient lower upper = sum (map euler [lower, lower+1 .. upper])
uint32_t sum_totient(uint32_t lower, uint32_t upper)
{
    uint32_t sum, i;

    sum = 0;
    for (i = lower; i <= upper; i++)
        sum = sum + euler_totient(i);
    return sum;
}

// Deleted unused benchmarking function

// modified slightly by Jerome
int main(int argc, char **argv)
{
    bool benchmark;
    parse_options(argc, argv, &benchmark);
    uint32_t result;

    if (argc-optind != 2){
        printf("\033[0;31mError:\033[0m Must provide exactly 2 arguments (rather than %d)\n", argc - optind);
        exit(EXIT_FAILURE);
    }

    const uint32_t lower = strtoul(argv[optind], NULL, 10);
    const uint32_t upper = strtoul(argv[optind + 1], NULL, 10);

    if (upper <= lower)
    {
        printf("\033[0;31mError:\033[0m Upper bound must be greater (or equal to) lower bound\n");
        return 1;
    }

    for (uint8_t i = 0; i< (uint8_t)(benchmark ? 5 : 1); i++){
        clock_t start = clock();
        result = sum_totient(lower, upper);
        double elapsed_time = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        // Modified print to be in line with rest of project
        printf("%u", result);
        if (benchmark)
            printf(",%f", elapsed_time);
        printf("\n");
    }

    return 0;
}
