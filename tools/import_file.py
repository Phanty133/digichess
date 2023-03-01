"""
	Generates a .EXT.h header and .EXT.c source file with a byte array that contains the bytes
	of a file

	Usage:
	python3 import_file.py <INPUT_PATH> <OUTPUT_PATH_IN_INCLUDES/SRC>
"""

import sys
import os

output_header_dir = os.path.join(os.path.dirname(__file__), "..", "include", sys.argv[2])
output_source_dir = os.path.join(os.path.dirname(__file__), "..", "src", sys.argv[2])

input_path = sys.argv[1]
input_name = os.path.basename(input_path)

output_header_name = f"{input_name}.h"
output_source_name = f"{input_name}.c"
output_header_path = os.path.join(output_header_dir, output_header_name)
output_source_path = os.path.join(output_source_dir, output_source_name)

file_ext = input_name.split(".")[-1]
file_name = "".join(input_name.split(".")[:-1])
arr_name = file_name.upper()

header_template = """\
#ifndef __{arr_name}_{ext}_H
#define __{arr_name}_{ext}_H
#include <stdint.h>

const uint8_t* {arr_name}();
const uint32_t {arr_name}_SIZE();

#endif
"""

source_template = """\
#include \"{inc_path}\"

#ifdef QUICK_UPLOAD
static const uint8_t {arr_name}_DATA[] = {{}};
#else
static const uint8_t {arr_name}_DATA[] = {{{data}}};
#endif

const uint8_t* {arr_name}() {{
	return {arr_name}_DATA;
}}

const uint32_t {arr_name}_SIZE() {{
	return sizeof({arr_name}_DATA);
}}
"""

format_params = {
	"arr_name": arr_name,
	"ext": file_ext.upper(),
	"inc_path": os.path.join(sys.argv[2], output_header_name),
	"data": ""
}

with open(input_path, "rb") as file:
	file_data = file.read()

	for char in file_data[:-1]:
		format_params["data"] += f"{hex(char)},"

	format_params["data"] += f"{hex(file_data[-1])}"

output_header = header_template.format(**format_params)
output_source = source_template.format(**format_params)

with open(output_header_path, "w") as file:
	file.write(output_header)

with open(output_source_path, "w") as file:
	file.write(output_source)
