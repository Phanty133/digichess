#include <linux/i2c-dev.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stdbool.h>

#define I2C_ADAPTER "/dev/i2c-0"
#define I2C_ADDR 0x40

bool write_i2c(int i2c_file, char* buf, int size) {
	return write(i2c_file, buf, size) != size;
}

bool read_i2c(int i2c_file, char* buf, int size) {
	return read(i2c_file, buf, size) != size;
}

int main() {
	int file;

	file = open(I2C_ADAPTER, O_RDWR);

	if (file < 0) {
		printf("Error opening I2C adapter!");
		exit(1);
	}

	char buf[10];

	buf[0] = 0x45;
	buf[1] = 0x46;
	buf[2] = 0x47;

	if (!write_i2c(file, buf, 3)) {
		printf("I2C write transaction failed! %s\n", strerror(errno));
	}

	if (read_i2c(file, buf, 5)) {
		for (int i = 0; i < 5; i++) {
			printf("%i ", buf[i]);
			printf("\n");
		}
	} else {
		printf("I2C read transaction failed! %s\n", strerror(errno));
	}

	return 0;
}