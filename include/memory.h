/// @file memory.h
/// @brief Simple memory manipulation functions

#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>

/// @brief Similar to C standard library's memset function.
/// @brief Sets the bytes at an address
/// @param str Target address
/// @param c Byte value to set to
/// @param n Number of bytes
void* memory_set(void* str, uint8_t c, uint32_t n);

/// @brief Similar to C standard library's memcpy function.
/// @brief Copies bytes from src to dest
/// @param dest Destination
/// @param src Source
/// @param n Number of bytes to copy
void* memory_copy(void* dest, const void* src, uint32_t n);

#endif