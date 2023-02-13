"""
	Generates a .lut.h header file that contains a float array of precalculated sqrt values
"""

import math
import os

output_dir = os.path.join(os.path.dirname(__file__), "..", "include", "lut")

output_name = f"sqrt.lut.h"
output_path = os.path.join(output_dir, output_name)
output_data = ""

arr_name = "SQRT_15BIT"
output_data += f"#ifndef __{arr_name}_TTF_H\n"
output_data += f"#define __{arr_name}_TTF_H\n"
output_data += f"static const float {arr_name}[] = {{"

max_val = 2 ** 15;

for i in range(0, max_val):
	val = math.sqrt(i)
	output_data += f"{val:.6f},"

output_data = output_data[:-1]
output_data += "};\n"
output_data += "#endif"

with open(output_path, "w") as file:
	file.write(output_data)