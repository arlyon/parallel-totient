#include <stdint.h>
#include <stdbool.h>

#pragma once

/**
 * Gets the greatest common divisor of two numbers.
 */
uint32_t greatest_common_divisor(uint32_t x, uint32_t y) {
    while (y != 0) {
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
bool relatively_prime(uint32_t x, uint32_t y) {
    return greatest_common_divisor(x, y) == 1;
}

/**
 * Calculates the euler totient.
 *
 * Gets the number of positive integers smaller
 * than n and relatively prime to n.
 */
uint32_t euler_totient(uint32_t n) {
    uint32_t length = 0;
    for (uint32_t i = 1; i < n; i++)
        if (relatively_prime(n, i))
            length++;
    return length;
}
