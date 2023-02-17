"""
	Generates a .EXT.h header file with a byte array that contains the bytes
	of a file

	Usage:
	python3 generate_file_header.py <INPUT_PATH> <OUTPUT_PATH_IN_INCLUDES>
"""

import sys
import os

output_dir = os.path.join(os.path.dirname(__file__), "..", "include", sys.argv[2])

input_path = sys.argv[1]
input_name = os.path.basename(input_path)

output_name = f"{input_name}.h"
output_path = os.path.join(output_dir, output_name)
output_data = ""

file_ext = input_name.split(".")[-1]
file_name = "".join(input_name.split(".")[:-1])
arr_name = file_name.upper()
output_data += f"#ifndef __{arr_name}_{file_ext.upper()}_H\n"
output_data += f"#define __{arr_name}_{file_ext.upper()}_H\n"
output_data += f"#include <stdint.h>\n"
output_data += f"static const uint8_t {arr_name}[] = {{"

with open(input_path, "rb") as file:
	file_data = file.read()

	for char in file_data[:-1]:
		output_data += f"{hex(char)},"

	output_data += f"{hex(file_data[-1])}"

output_data += "};\n"
output_data += "#endif"

with open(output_path, "w") as file:
	file.write(output_data)