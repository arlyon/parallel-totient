#pragma once

#include <omp.h>
#include <time.h>

#ifndef NDEBUG
#define DEBUG true
#else
#define DEBUG false
#endif

omp_lock_t lock;

#define debug_print(fmt, ...)                                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        if (DEBUG)                                                                                                     \
        {                                                                                                              \
            time_t t = time(NULL);                                                                                     \
            struct tm tm = *localtime(&t);                                                                             \
            omp_set_lock(&lock);                                                                                       \
            fprintf(stderr, "%02d:%02d:%02d ", tm.tm_hour, tm.tm_min, tm.tm_sec);                                      \
            fprintf(stderr, "[%s:%d] ", __FILENAME__, __LINE__);                                                       \
            fprintf(stderr, "[thread %03d] ", omp_get_thread_num());                                                   \
            fprintf(stderr, fmt, __VA_ARGS__);                                                                         \
            omp_unset_lock(&lock);                                                                                     \
        }                                                                                                              \
    } while (0)
