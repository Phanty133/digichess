#ifndef __STOCKFISH_H
#define __STOCKFISH_h

#include <stdint.h>
#include <pic32mx.h>
#include "uart.h"
#include "sys_defines.h"
#include "bitops.h"

#define __I2C_ADDRESS (0x40)
#define __I2C_SLAVE_IF (1 << 30)
#define __I2C_SLAVE_IE (1 << 30)
#define __I2C_SLAVE_IP (3 << 10)
#define __I2C_SLAVE_IS (1 << 8)

#define __I2C_MASTER_IF (1 << 29)
#define __I2C_BUS_IF (1 << 31)

/// @brief Configures the I2C bus for the Stockfish interface
void stockfish_setup();

#endif