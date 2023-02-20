/// @file stringops.h
/// @brief Functions for string operations

#ifndef __STRINGOPS_H
#define __STRINGOPS_H

#include <stdint.h>

/// @brief Converts num to char*. Here only because I couldn't get sprintf to compile
/// @param num Number to convert
/// @param buf Buffer to write to
/// @param bufsize Buffer size
void num2char(uint32_t num, char* buf, const uint32_t bufsize);

#endif