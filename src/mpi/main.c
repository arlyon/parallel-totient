#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include "../common.h"

int main(int argc, char** argv)
{
    if (argc-optind != 2){
        printf("\033[0;31mError:\033[0m Must provide exactly 2 arguments (rather than %d)\n", argc - optind);
        exit(EXIT_FAILURE);
    }

    // Variables
    int processors, id;
    uint32_t total;
    const uint32_t lower = strtoul(argv[optind], NULL, 10);
    const uint32_t upper = strtoul(argv[optind + 1], NULL, 10);

    if (upper <= lower)
    {
        printf("\033[0;31mError:\033[0m Upper bound must be greater (or equal to) lower bound\n");
        return 1;
    }

    // MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &processors);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    uint32_t sum = 0;
    for (int i = id+lower; i <= upper; i+=processors){
        sum += euler_totient(i);
    }

    MPI_Reduce(&sum, &total, 1, MPI_UNSIGNED_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    if (id == 0) {
        printf("%u\n", total);
    }
    MPI_Finalize();
    exit(0);
}
