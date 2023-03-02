#include "files/images/bishop.bmp.h"

#ifdef QUICK_UPLOAD
static const uint8_t BISHOP_DATA[] = {};
#else
static const uint8_t BISHOP_DATA[] = {0x42,0x4d,0x30,0x3,0x0,0x0,0x0,0x0,0x0,0x0,0x72,0x0,0x0,0x0,0x28,0x0,0x0,0x0,0x2d,0x0,0x0,0x0,0x2d,0x0,0x0,0x0,0x1,0x0,0x4,0x0,0x2,0x0,0x0,0x0,0xbe,0x2,0x0,0x0,0xd7,0xd,0x0,0x0,0xd7,0xd,0x0,0x0,0xf,0x0,0x0,0x0,0xf,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x2c,0x12,0xe,0x0,0x51,0x1f,0x17,0x0,0x2f,0x2d,0x2a,0x0,0x7e,0x31,0x22,0x0,0xa8,0x40,0x2d,0x0,0x56,0x58,0x56,0x0,0x7b,0x7e,0x7c,0x0,0x83,0x86,0x84,0x0,0x8d,0x90,0x8e,0x0,0x9e,0xa1,0x9f,0x0,0xa8,0xab,0xa9,0x0,0xba,0xbd,0xba,0x0,0xd4,0xd7,0xd5,0x0,0xff,0xff,0xff,0x0,0x2c,0x55,0x1,0x50,0x0,0x0,0x2c,0x55,0x1,0x50,0x0,0x0,0x2c,0x55,0x1,0x50,0x0,0x0,0x2c,0x55,0x1,0x50,0x0,0x0,0x6,0x55,0x2,0x54,0x1c,0x55,0x2,0x54,0x6,0x55,0x1,0x50,0x0,0x0,0x0,0xa,0x55,0x55,0x54,0x0,0x1,0x0,0xa,0x22,0x0,0x6,0x44,0x54,0x42,0x0,0x8,0x22,0x0,0xb,0x21,0x0,0x4,0x55,0x55,0x50,0x0,0x0,0x0,0xa,0x55,0x55,0x51,0x6,0x73,0x0,0x18,0x0,0x0,0xb,0x3,0x76,0x1,0x55,0x55,0x50,0x0,0x0,0x0,0xc,0x55,0x55,0x54,0x10,0x6c,0xde,0x8,0xee,0x0,0x6,0xda,0x7a,0xde,0x0,0x8,0xee,0x0,0xb,0xdc,0x60,0x14,0x55,0x55,0x50,0x0,0x0,0x6,0x55,0x2,0x52,0x8,0x0,0x0,0xe,0x33,0x67,0xce,0xee,0xc7,0x63,0x30,0x0,0x6,0x0,0x2,0x2,0x6,0x55,0x1,0x50,0x0,0x0,0x8,0x55,0x2,0x54,0x6,0x22,0x0,0x14,0x11,0x10,0x0,0x60,0x0,0x11,0x12,0x22,0x22,0x24,0x8,0x55,0x1,0x50,0x0,0x0,0x10,0x55,0x2,0x42,0x8,0x0,0x2,0x2,0x2,0x45,0xe,0x55,0x1,0x50,0x0,0x0,0xe,0x55,0x0,0x12,0x41,0x0,0x67,0xab,0xcb,0xa7,0x60,0x1,0x45,0x0,0xc,0x55,0x1,0x50,0x0,0x0,0xe,0x55,0x2,0x10,0x2,0xbe,0xa,0xee,0x2,0xb0,0x2,0x15,0xc,0x55,0x1,0x50,0x0,0x0,0xe,0x55,0x2,0x6,0xc,0xbb,0x2,0xb6,0x2,0x5,0xc,0x55,0x1,0x50,0x0,0x0,0xe,0x55,0x10,0x0,0x2,0x5,0xc,0x55,0x1,0x50,0x0,0x0,0xe,0x55,0x2,0x20,0xc,0xdd,0x2,0xd0,0x2,0x25,0xc,0x55,0x1,0x50,0x0,0x0,0xe,0x55,0x2,0x40,0x2,0x6e,0xa,0xee,0x2,0x60,0x2,0x45,0xc,0x55,0x1,0x50,0x0,0x0,0xe,0x55,0x2,0x52,0x2,0x6,0x8,0xbb,0x2,0xb6,0x2,0x2,0xe,0x55,0x1,0x50,0x0,0x0,0xe,0x55,0x2,0x52,0xc,0x0,0x2,0x2,0xe,0x55,0x1,0x50,0x0,0x0,0xe,0x55,0x2,0x20,0x2,0x6c,0x8,0xdd,0x0,0x6,0xdc,0x60,0x25,0x0,0xc,0x55,0x1,0x50,0x0,0x0,0xc,0x55,0x2,0x54,0x2,0x6,0xc,0xee,0x2,0xe6,0x2,0x4,0xc,0x55,0x1,0x50,0x0,0x0,0xc,0x55,0x2,0x51,0x2,0xe,0xe,0xee,0x2,0x1,0xc,0x55,0x1,0x50,0x0,0x0,0xc,0x55,0x2,0x50,0x2,0x6e,0xe,0xee,0x2,0x60,0xc,0x55,0x1,0x50,0x0,0x0,0xc,0x55,0x0,0xc,0x50,0x8e,0xee,0xee,0xed,0x3d,0x6,0xee,0x2,0x80,0xc,0x55,0x1,0x50,0x0,0x0,0xc,0x55,0x0,0xc,0x50,0x7e,0xee,0xee,0xec,0xc,0x6,0xee,0x2,0x70,0xc,0x55,0x1,0x50,0x0,0x0,0xc,0x55,0x0,0x14,0x50,0x6e,0xee,0xed,0xb7,0x7,0xbd,0xee,0xee,0x60,0xc,0x55,0x1,0x50,0x0,0x0,0xc,0x55,0x0,0x14,0x52,0xe,0xee,0xe6,0x0,0x0,0x6,0xee,0xee,0x2,0xc,0x55,0x1,0x50,0x0,0x0,0xc,0x55,0x0,0x14,0x54,0x9,0xee,0xee,0xdb,0xb,0xde,0xee,0xe9,0x4,0xc,0x55,0x1,0x50,0x0,0x0,0xe,0x55,0x0,0x12,0x10,0xde,0xee,0xec,0xc,0xee,0xee,0xd0,0x15,0x0,0xc,0x55,0x1,0x50,0x0,0x0,0xe,0x55,0x0,0x12,0x40,0x3e,0xee,0xee,0x7e,0xee,0xee,0x30,0x45,0x0,0xc,0x55,0x1,0x50,0x0,0x0,0xe,0x55,0x0,0x6,0x54,0x3,0xde,0x0,0x6,0xee,0x2,0xd3,0x2,0x4,0xe,0x55,0x1,0x50,0x0,0x0,0x10,0x55,0x0,0xe,0x40,0xa,0xee,0xee,0xea,0x0,0x45,0x0,0xe,0x55,0x1,0x50,0x0,0x0,0x10,0x55,0x0,0xc,0x54,0x10,0x3b,0xeb,0x30,0x14,0x10,0x55,0x1,0x50,0x0,0x0,0x12,0x55,0x0,0x8,0x54,0x0,0x0,0x4,0x12,0x55,0x1,0x50,0x0,0x0,0x12,0x55,0x0,0x8,0x54,0x0,0x60,0x4,0x12,0x55,0x1,0x50,0x0,0x0,0x12,0x55,0x0,0x8,0x52,0xd,0xed,0x2,0x12,0x55,0x1,0x50,0x0,0x0,0x12,0x55,0x0,0x8,0x51,0x3e,0xee,0x31,0x12,0x55,0x1,0x50,0x0,0x0,0x12,0x55,0x0,0x8,0x52,0xc,0xec,0x2,0x12,0x55,0x1,0x50,0x0,0x0,0x14,0x55,0x0,0x6,0x0,0x0,0x5,0x0,0x12,0x55,0x1,0x50,0x0,0x0,0x14,0x55,0x2,0x52,0x2,0x22,0x14,0x55,0x1,0x50,0x0,0x0,0x2c,0x55,0x1,0x50,0x0,0x0,0x2c,0x55,0x1,0x50,0x0,0x0,0x2c,0x55,0x1,0x50,0x0,0x0,0x2c,0x55,0x1,0x50,0x0,0x0,0x2c,0x55,0x1,0x50,0x0,0x1};
#endif

const uint8_t* BISHOP() {
	return BISHOP_DATA;
}

const uint32_t BISHOP_SIZE() {
	return sizeof(BISHOP_DATA);
}
