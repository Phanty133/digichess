# digichess
Mini-project for KTH IS1200

## Usage
- `make` - Compile
- `make install` - Install onto the Chipkit
- `make dev` - Compile and install
- `make test` - Run tests
- `make clean` - Clean build directory

To compile without font rendering (Reduces program upload time), set the make `DEFINES` variable to `DISABLE_FONT_RENDERING`, e.g. `make dev DEFINES=DISABLE_FONT_RENDERING`
