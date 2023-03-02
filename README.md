# digichess
Mini-project for KTH IS1200

## Usage
- `make` - Compile
- `make install` - Install onto the Chipkit
- `make dev` - Compile and install
- `make test` - Run tests
- `make clean` - Clean build directory

### Compiler flags

To compile without font rendering (Reduces program upload time), set the make `DEFINES` variable to `DISABLE_FONT_RENDERING`, e.g. `make dev DEFINES=DISABLE_FONT_RENDERING`.

To compile without uploading any file, set the make `DEFINES` variable to `QUICK_UPLOAD`, e.g. `make dev DEFINES=QUICK_UPLOAD`.

### Adding files

To add a file to the microcontroller, run `python tools/generate_file_header.py <PATH_TO_FILE> <OUTPUT_DIR_IN_INCLUDES>`. A header file containing a const byte array with the file data will be generated in the specified directory in includes.

## Notes

### Timers used
- **Timer 2**: Grid update
- **Timer 3**: Buzzer
- **Timer 4**: -
- **Timer 5**: -
