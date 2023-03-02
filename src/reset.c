#include "reset.h"

void software_reset() {
	// OSCCON unlock sequence
	SYSKEY = 0x00000000; // Write invalid key to force lock
	SYSKEY = 0xAA996655; // Write key1 to SYSKEY
	SYSKEY = 0x556699AA; // Write key2 to SYSKEY

	RSWRSTSET = 1; // Arm reset

	unsigned int temp;
	temp = RSWRST; // Trigger reset

	while(1); // Delay until reset
}