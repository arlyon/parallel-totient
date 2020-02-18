#pragma once

#include <omp.h>
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
           "\t-t : The number of threads to use\n"
           "\t     Defaults to the number of logical cores on this machine\n"
           "\t-s : The scheduler to use (static|dynamic|guided|auto)\n"
           "\t     Defaults to static\n"
           "\t-c : The batch size"
           "\t     Defaults to automatically determining the best"
           "\n");
    printf("Example usage:\n\t%s [-t 4] LOWER UPPER\n\n", argv[0]);
}

void parseOptions(int argc, char **argv, uint32_t *threads, omp_sched_t *scheduler, uint32_t *batch_size)
{
    opterr = false;
    int opt;
    while ((opt = getopt(argc, argv, "t:s:b:")) != -1)
    {
        switch (opt)
        {
        case 't':
            *threads = strtoul(optarg, NULL, 10);
            break;
        case 's':
            if (strcmp(optarg, "static"))
                *scheduler = omp_sched_static;
            else if (strcmp(optarg, "dynamic"))
                *scheduler = omp_sched_dynamic;
            else if (strcmp(optarg, "auto"))
                *scheduler = omp_sched_auto;
            else if (strcmp(optarg, "guided"))
                *scheduler = omp_sched_guided;
            else
            {
                printUsage(argv);
                printf("\033[0;31mError:\033[0m Unknown argument for option %c: %s\n", optopt, optarg);
                exit(EXIT_FAILURE);
            }
            break;
        case 'b':
            *batch_size = strtoul(optarg, NULL, 10);
            break;
        default:
            printUsage(argv);
            printf("\033[0;31mError:\033[0m Unknown option: %c\n", optopt);
            exit(EXIT_FAILURE);
        }
    }
}
