/**
 * Written by Jerome Illgner (H00263642) for Distributed and Parallel Technologies
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include "../common.h"
#include "../cli.h"

__uint32_t sum_totient(lower, upper, processes, id, timed){
    double elapsed_time;
    uint32_t total;

    MPI_Barrier(MPI_COMM_WORLD);
    double local_time = -MPI_Wtime();

    uint32_t sum = 0;
    for (int i = id+lower; i <= upper; i+=processes){
        sum += euler_totient(i);
    }

    // Reduce euler sum and time taken back to root process
    MPI_Reduce(&sum, &total, 1, MPI_UNSIGNED_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    local_time+= MPI_Wtime();
    MPI_Reduce(&local_time, &elapsed_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);


    if (id == 0) {
        printf("%u", total);
        if (timed)
            printf(",%f", elapsed_time);
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    bool benchmark;
    parse_options(argc, argv, &benchmark);
    // Ensuring correct number of arguments
    if (argc-optind != 2){
        printf("\033[0;31mError:\033[0m Must provide exactly 2 arguments (rather than %d)\n", argc - optind);
        exit(EXIT_FAILURE);
    }

    // Variables
    int processes, id;
    const uint32_t lower = strtoul(argv[optind], NULL, 10);
    const uint32_t upper = strtoul(argv[optind + 1], NULL, 10);

    // Ensuring that arguments were supplied in correct order
    if (upper <= lower)
    {
        printf("\033[0;31mError:\033[0m Upper bound must be greater (or equal to) lower bound\n");
        return 1;
    }

    // MPI Setup
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);




    // MPI teardown
    MPI_Finalize();
    exit(0);
}
