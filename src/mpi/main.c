/**
 * Written by Jerome Illgner (H00263642) for Distributed and Parallel Technologies
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include "../common.h"

int main(int argc, char** argv)
{
    // Ensuring correct number of arguments
    if (argc-optind != 2){
        printf("\033[0;31mError:\033[0m Must provide exactly 2 arguments (rather than %d)\n", argc - optind);
        exit(EXIT_FAILURE);
    }

    // Variables
    int processes, id;
    uint32_t total;
    double elapsed_time;
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

    // MPI Timing
    MPI_Barrier(MPI_COMM_WORLD);
    double local_time = MPI_Wtime();

    // Euler's totient distributing work evenly across processes. Done by incrementing by number of processors.
    uint32_t sum = 0;
    for (int i = id+lower; i <= upper; i+=processes){
        sum += euler_totient(i);
    }

    // Reduce euler sum and time taken back to root process
    MPI_Reduce(&sum, &total, 1, MPI_UNSIGNED_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    local_time = MPI_Wtime() - local_time;
    MPI_Reduce(&local_time, &elapsed_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);


    if (id == 0) {
        printf("The sum of euler totients in range [%u...%u] is %u.\n Time taken was %f.\n", lower, upper, sum, elapsed_time);
    }

    // MPI teardown
    MPI_Finalize();
    exit(0);
}
