#include <stdbool.h>
#include <stdint.h>

/**
 * Adapted by Alexander Lyon (H00276422) in 2020 from sample sequential implementation for coursework.
 *
 * Greg Michaelson 14/10/2003
 * Patrick Maier   29/01/2010 [enforced ANSI C compliance] This program calculates the sum of the totients between
 * a lower and an upper limit using C longs. It is based on earlier work by:
 * Phil Trinder, Nathan Charles, Hans-Wolfgang Loidl and Colin Runciman
 */

#pragma once

/**
 * Gets the greatest common divisor of two numbers.
 */
uint32_t greatest_common_divisor(uint32_t x, uint32_t y)
{
    while (y != 0)
    {
        uint32_t temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

/**
 * Checks if parameter x and y are relatively prime.
 * @return True if prime
 */
bool relatively_prime(uint32_t x, uint32_t y)
{
    return greatest_common_divisor(x, y) == 1;
}

/**
 * Calculates the euler totient.
 *
 * Gets the number of positive integers smaller
 * than n and relatively prime to n.
 */
uint32_t euler_totient(uint32_t n)
{
    uint32_t length = 0;
    for (uint32_t i = 1; i < n; i += (n % 2 == 0) ? 2 : 1)
        if (relatively_prime(n, i))
            length++;
    return length;
}
