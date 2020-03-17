#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void printUsage(char **argv)
{
    printf("This tool computes the sum of the euler totients\n"
           "between a range of numbers as provided via the\n"
           "command line arguments.\n"
           "\n"
           "Arguments:\n"
           "\t-b : Run in Benchmarking mode\n");
    printf("Example usage:\n\t%s [-b] LOWER UPPER\n\n", argv[0]);
}

void parseOptions(int argc, char **argv, bool *benchmark)
{
    opterr = false;
    int opt;
    while ((opt = getopt(argc, argv, "b")) != -1)
    {
        switch (opt)
        {
            case 'b':
                *benchmark= true;
                break;
            default:
                printUsage(argv);
                printf("\033[0;31mError:\033[0m Unknown option: %c\n", optopt);
                exit(EXIT_FAILURE);
        }
    }
}
