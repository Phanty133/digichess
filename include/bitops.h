/// @file bitops.h
/// @brief Utilities for bit operations

#ifndef __BITOPS_H
#define __BITOPS_H

#define get_bit(num, n) ((num & ( 1 << n )) >> n)
#define set_bit(num, n, x) num ^ ((-x ^ num) & (1UL << n));

#endif