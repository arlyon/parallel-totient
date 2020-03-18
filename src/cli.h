#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_usage(char **argv)
{
    printf("This tool computes the sum of the euler totients\n"
           "between a range of numbers as provided via the\n"
           "command line arguments.\n"
           "\n"
           "Arguments:\n"
           "\t-p : Enable the profiler and print out running time\n");
    printf("Example usage:\n\t%s [-b] LOWER UPPER\n\n", argv[0]);
}

void parse_options(int argc, char **argv, bool *time)
{
    opterr = false;
    int opt;
    while ((opt = getopt(argc, argv, "p")) != -1)
    {
        switch (opt)
        {
            case 'p':
                *time = true;
                break;
            default:
                print_usage(argv);
                printf("\033[0;31mError:\033[0m Unknown option: %c\n", optopt);
                exit(EXIT_FAILURE);
        }
    }
}
