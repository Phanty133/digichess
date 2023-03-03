#include "drivers/stockfish/stockfish.h"

static uint32_t calc_baudrate(uint32_t freq) {
	double BRG = (1 / (2 * freq)) - 0.000000104;
    BRG *= (SYS_FREQ / 2) - 2;

	return BRG;
}

static void release_clock() {
	I2C1CONSET = (1 << 12);
}

static void hold_clock() {
	I2C1CONCLR = (1 << 12);
}

void stockfish_setup() {
	I2C1CON =
		(1 << 15) // ON
		| (1 << 6); // Clock stretching

	I2C1ADD = __I2C_ADDRESS;
	I2C1MSK = 0;
	I2C1BRG = calc_baudrate(100000);

	IFSCLR(0) = __I2C_SLAVE_IF;
	IECSET(0) = __I2C_SLAVE_IE;
	IPCSET(6) = __I2C_SLAVE_IP | __I2C_SLAVE_IS;

	ENABLE_INTERRUPTS;
}

void i2c_isr() {
	static uint32_t dIndex;

	if (IFS(0) & __I2C_MASTER_IF) {
		IFSCLR(0) = __I2C_MASTER_IF | __I2C_SLAVE_IF;
		return;
	}

	if (IFS(0) & __I2C_BUS_IF) {
		IFSCLR(0) = __I2C_BUS_IF | __I2C_SLAVE_IF;
		return;
	}

	uint8_t action = get_bit(I2C1STAT, 2); // R/W bit
	uint8_t data_type = get_bit(I2C1STAT, 5); // D/A bit

	if (!action && !data_type) {
		// R/W = 0 -> Slave read
		// D/A = 0 -> Last byte is address

		uint32_t addr = I2C1RCV;
	} else if (!action && data_type) {
		// R/W = 0 -> Slave read
		// D/A = 0 -> Last byte is data

		if (I2C1STAT & (1 << 6)){
			// TODO: Handle buffer overflow error
			// uart_write_line("I2C Rx Buffer Oveflowtnirk");
		}

		uint32_t data = I2C1RCV;

		uart_write("Data: ");
		uart_write_num(data, 1);
	} else if (action && !data_type) {
		// R/W = 0 -> Slave send
		// D/A = 0 -> Last byte is address

		// Start of write to master. This is the address

		uint32_t addr = I2C1RCV;

		I2C1TRN = 69;

		dIndex = 0;
	} else if (action && data_type) {
		// R/W = 1 -> Slave send
		// D/A = 1 -> Last byte is data

		// Start of write to master. Send a data byte

		I2C1TRN = 42;
	}

	release_clock();

	if (I2C1STAT & (1 << 7)) {
		uart_write_line("I2C bus collision");
	}

	IFSCLR(0) = __I2C_SLAVE_IF;
}
