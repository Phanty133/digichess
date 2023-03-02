#include "files/images/queen.bmp.h"

#ifdef QUICK_UPLOAD
static const uint8_t QUEEN_DATA[] = {};
#else
static const uint8_t QUEEN_DATA[] = {0x42,0x4d,0xfe,0x4,0x0,0x0,0x0,0x0,0x0,0x0,0xc6,0x0,0x0,0x0,0x7c,0x0,0x0,0x0,0x2d,0x0,0x0,0x0,0x2d,0x0,0x0,0x0,0x1,0x0,0x4,0x0,0x0,0x0,0x0,0x0,0x38,0x4,0x0,0x0,0xd7,0xd,0x0,0x0,0xd7,0xd,0x0,0x0,0xf,0x0,0x0,0x0,0xf,0x0,0x0,0x0,0x0,0xf8,0x0,0x0,0xe0,0x7,0x0,0x0,0x1f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x42,0x47,0x52,0x73,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x33,0x15,0xf,0x0,0x55,0x22,0x19,0x0,0x2b,0x2b,0x29,0x0,0x7c,0x30,0x20,0x0,0xa8,0x40,0x2d,0x0,0x58,0x5b,0x59,0x0,0xac,0x5e,0x54,0x0,0x79,0x7c,0x7a,0x0,0x87,0x8a,0x88,0x0,0x92,0x95,0x93,0x0,0xa1,0xa4,0xa2,0x0,0xaf,0xb2,0xb0,0x0,0xc0,0xc4,0xc1,0x0,0xff,0xff,0xff,0x0,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x54,0x22,0x11,0x10,0x0,0x0,0x0,0x0,0x0,0x11,0x12,0x24,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x0,0x0,0x3,0x66,0x66,0x88,0x88,0x86,0x66,0x63,0x0,0x0,0x5,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x54,0xc,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xec,0x4,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x54,0x8,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xe8,0x4,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x16,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xe6,0x15,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x10,0xce,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xc0,0x15,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x3,0x36,0x66,0x88,0x88,0x86,0x66,0x33,0x0,0x0,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x52,0xa,0x86,0x33,0x33,0x0,0x0,0x3,0x33,0x36,0x8a,0x2,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x52,0xe,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0x2,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x50,0x3a,0xcd,0xdd,0xde,0xee,0xee,0xee,0xdd,0xdd,0xca,0x30,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x10,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x15,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x51,0xb,0xee,0xdc,0xcb,0xaa,0x99,0x99,0x9a,0xab,0xcc,0xde,0xeb,0x1,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x20,0x9e,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0x90,0x25,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x0,0x8b,0xdd,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xed,0xdb,0x80,0x5,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x0,0x0,0x0,0x0,0x33,0x36,0x66,0x66,0x66,0x33,0x30,0x0,0x0,0x0,0x5,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x9,0xed,0x60,0x3,0x33,0x0,0x0,0x0,0x0,0x0,0x33,0x0,0x6b,0xe9,0x5,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x54,0xd,0xee,0x30,0x3e,0xee,0x60,0x9e,0xee,0x90,0x6e,0xee,0x30,0x3e,0xed,0x4,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x52,0xe,0xe8,0x0,0x3e,0xee,0x0,0x6e,0xee,0x60,0xe,0xee,0x30,0x8,0xee,0x2,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x51,0x3e,0xd0,0x11,0x3e,0xe9,0x1,0x3e,0xee,0x31,0x9,0xee,0x31,0x10,0xde,0x31,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x50,0x6e,0x30,0x51,0x3e,0xe3,0x12,0xe,0xee,0x2,0x13,0xee,0x31,0x50,0x3e,0x60,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x50,0x99,0x4,0x51,0x3e,0xd0,0x24,0xc,0xec,0x4,0x20,0xde,0x31,0x54,0x9,0x90,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x40,0xa0,0x15,0x51,0x3e,0x60,0x55,0x8,0xe8,0x5,0x50,0x6e,0x1,0x55,0x10,0xa0,0x45,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x20,0x30,0x55,0x52,0xe,0x1,0x55,0x16,0xe6,0x15,0x51,0xe,0x2,0x55,0x50,0x30,0x25,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x10,0x4,0x55,0x52,0xb,0x4,0x55,0x10,0xe0,0x15,0x54,0xb,0x2,0x55,0x54,0x0,0x15,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x0,0x15,0x55,0x52,0x3,0x5,0x55,0x20,0xd0,0x25,0x55,0x3,0x2,0x55,0x55,0x10,0x5,0x55,0x55,0x50,0x0,0x55,0x55,0x41,0x0,0x55,0x55,0x52,0x0,0x25,0x55,0x40,0x60,0x45,0x55,0x20,0x2,0x55,0x55,0x50,0x1,0x45,0x55,0x50,0x0,0x55,0x54,0x3,0x30,0x45,0x55,0x52,0x0,0x55,0x55,0x50,0x0,0x55,0x55,0x50,0x2,0x55,0x55,0x40,0x33,0x4,0x55,0x50,0x0,0x55,0x51,0x3e,0xe3,0x15,0x55,0x52,0x1,0x55,0x55,0x51,0x1,0x55,0x55,0x51,0x2,0x55,0x55,0x13,0xee,0x31,0x55,0x50,0x0,0x55,0x51,0x3e,0xe3,0x15,0x55,0x40,0x2,0x55,0x55,0x52,0x2,0x55,0x55,0x52,0x0,0x45,0x55,0x13,0xee,0x31,0x55,0x50,0x0,0x55,0x54,0x3,0x30,0x45,0x54,0x3,0x30,0x45,0x55,0x51,0x1,0x55,0x55,0x40,0x33,0x4,0x55,0x40,0x33,0x4,0x55,0x50,0x0,0x55,0x55,0x41,0x14,0x55,0x51,0x3e,0xe3,0x15,0x55,0x10,0x30,0x15,0x55,0x13,0xee,0x31,0x55,0x54,0x11,0x45,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x51,0x3e,0xe3,0x15,0x54,0xa,0xea,0x4,0x55,0x13,0xee,0x31,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x54,0x3,0x30,0x45,0x54,0xa,0xea,0x4,0x55,0x40,0x33,0x4,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x55,0x41,0x14,0x55,0x55,0x10,0x30,0x15,0x55,0x54,0x11,0x45,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x52,0x12,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x50,0x0,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x50,0x0};
#endif

const uint8_t* QUEEN() {
	return QUEEN_DATA;
}

const uint32_t QUEEN_SIZE() {
	return sizeof(QUEEN_DATA);
}
