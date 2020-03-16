#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common.h"
#include "cli.h"
#include "logging.h"

/**
 * Returns the sum of all the euler_totients
 * between lower and upper.
 */
uint32_t sum_totient(const uint32_t lower, const uint32_t upper)
{
    uint32_t sum = 0;

#pragma omp parallel for schedule(runtime) reduction(+ : sum)
    for (uint32_t i = lower; i <= upper; i++)
    {
        debug_print("Calculating euler totient for %d\n", i);
        sum += euler_totient(i);
    }

    return sum;
}

int main(int argc, char **argv)
{
    omp_init_lock(&lock);

    uint32_t threads = omp_get_num_procs();
    omp_sched_t scheduler = omp_sched_static;
    uint32_t batch_size = 0;

    parseOptions(argc, argv, &threads, &scheduler, &batch_size);

    omp_set_num_threads(threads);
    omp_set_schedule(scheduler, batch_size);
    debug_print("Using %d thread(s)\n", threads);
    debug_print("Using %d scheduler\n", scheduler);

    if (argc - optind != 2)
    {
        printUsage(argv);
        printf("\033[0;31mError:\033[0m Must provide exactly 2 arguments (rather "
               "than %d)\n",
               argc - optind);
        exit(EXIT_FAILURE);
    }
    const uint32_t lower = strtoul(argv[optind], NULL, 10);
    const uint32_t upper = strtoul(argv[optind + 1], NULL, 10);

    if (upper < lower)
    {
        printUsage(argv);
        printf("\033[0;31mError:\033[0m Upper bound must be greater (or equal to) "
               "lower bound\n");
        return 1;
    }

    debug_print("Running totient range for [%d, %d]\n", lower, upper);
    printf("%u\n", sum_totient(lower, upper));
}
