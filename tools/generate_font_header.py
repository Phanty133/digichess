"""
	Generates a .ttf.h header file with a byte array that contains the bytes
	of a .ttf file
"""

import sys
import os

output_dir = os.path.join(os.path.dirname(__file__), "..", "include", "fonts")

input_path = sys.argv[1]
input_name = os.path.basename(input_path)

output_name = f"{input_name}.h"
output_path = os.path.join(output_dir, output_name)
output_data = ""

arr_name = input_name.replace(".ttf", "").upper()
output_data += f"#ifndef __{arr_name}_TTF_H\n"
output_data += f"#define __{arr_name}_TTF_H\n"
output_data += f"static const char {arr_name}[] = {{"

with open(input_path, "rb") as file:
	file_data = file.read()

	for char in file_data[:-1]:
		output_data += f"{hex(char)},"

	output_data += f"{hex(file_data[-1])}"

output_data += "};\n"
output_data += "#endif"

with open(output_path, "w") as file:
	file.write(output_data)