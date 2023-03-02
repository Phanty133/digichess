#include "files/images/knight.bmp.h"

#ifdef QUICK_UPLOAD
static const uint8_t KNIGHT_DATA[] = {};
#else
static const uint8_t KNIGHT_DATA[] = {0x42,0x4d,0xda,0x7,0x0,0x0,0x0,0x0,0x0,0x0,0x3e,0x4,0x0,0x0,0x7c,0x0,0x0,0x0,0x2d,0x0,0x0,0x0,0x2d,0x0,0x0,0x0,0x1,0x0,0x8,0x0,0x1,0x0,0x0,0x0,0x9c,0x3,0x0,0x0,0xd7,0xd,0x0,0x0,0xd7,0xd,0x0,0x0,0xed,0x0,0x0,0x0,0xed,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0x0,0xff,0x0,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x42,0x47,0x52,0x73,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,0x1,0x0,0x0,0x1,0x1,0x1,0x0,0x2,0x1,0x1,0x0,0x2,0x2,0x1,0x0,0x2,0x2,0x2,0x0,0x4,0x3,0x3,0x0,0x5,0x3,0x3,0x0,0x6,0x3,0x3,0x0,0x7,0x4,0x3,0x0,0x5,0x4,0x4,0x0,0x5,0x5,0x5,0x0,0x9,0x5,0x4,0x0,0x9,0x5,0x5,0x0,0x6,0x6,0x6,0x0,0xb,0x6,0x5,0x0,0xc,0x6,0x5,0x0,0x7,0x7,0x6,0x0,0x7,0x7,0x7,0x0,0x8,0x7,0x7,0x0,0xd,0x7,0x6,0x0,0xe,0x7,0x6,0x0,0xf,0x7,0x6,0x0,0x9,0x8,0x8,0x0,0xa,0x9,0x9,0x0,0x13,0x9,0x8,0x0,0x14,0x9,0x8,0x0,0x14,0xa,0x8,0x0,0x18,0xb,0x9,0x0,0xc,0xc,0xc,0x0,0xd,0xc,0xc,0x0,0x19,0xc,0xa,0x0,0x1a,0xc,0xa,0x0,0x1b,0xc,0xa,0x0,0xd,0xd,0xd,0x0,0xe,0xd,0xd,0x0,0x1c,0xd,0xa,0x0,0x1d,0xd,0xa,0x0,0x1c,0xd,0xb,0x0,0x1d,0xd,0xb,0x0,0x21,0xd,0xa,0x0,0x1e,0xd,0xb,0x0,0xf,0xe,0xe,0x0,0x1f,0xe,0xb,0x0,0x20,0xe,0xb,0x0,0x21,0xe,0xc,0x0,0x11,0x10,0xf,0x0,0x28,0x10,0xc,0x0,0x29,0x10,0xc,0x0,0x27,0x10,0xd,0x0,0x11,0x11,0x11,0x0,0x13,0x11,0x11,0x0,0x28,0x11,0xd,0x0,0x28,0x11,0xe,0x0,0x2d,0x11,0xd,0x0,0x12,0x12,0x12,0x0,0x13,0x12,0x12,0x0,0x14,0x12,0x12,0x0,0x2e,0x12,0xe,0x0,0x14,0x13,0x12,0x0,0x2f,0x12,0xe,0x0,0x2e,0x13,0xf,0x0,0x32,0x14,0xf,0x0,0x33,0x14,0xf,0x0,0x33,0x14,0x10,0x0,0x16,0x15,0x15,0x0,0x32,0x15,0x10,0x0,0x37,0x15,0x11,0x0,0x18,0x17,0x16,0x0,0x39,0x16,0x11,0x0,0x18,0x17,0x17,0x0,0x3a,0x17,0x11,0x0,0x3b,0x17,0x11,0x0,0x3a,0x17,0x12,0x0,0x1a,0x19,0x18,0x0,0x3e,0x18,0x13,0x0,0x3f,0x18,0x13,0x0,0x3f,0x19,0x13,0x0,0x40,0x19,0x13,0x0,0x1c,0x1a,0x1a,0x0,0x43,0x1a,0x14,0x0,0x47,0x1c,0x15,0x0,0x49,0x1c,0x16,0x0,0x1f,0x1e,0x1e,0x0,0x4a,0x1d,0x16,0x0,0x4d,0x1e,0x17,0x0,0x21,0x20,0x20,0x0,0x52,0x20,0x18,0x0,0x56,0x21,0x1a,0x0,0x23,0x23,0x23,0x0,0x58,0x22,0x1a,0x0,0x59,0x22,0x1a,0x0,0x26,0x24,0x24,0x0,0x5e,0x24,0x1c,0x0,0x61,0x26,0x1d,0x0,0x29,0x28,0x28,0x0,0x64,0x27,0x1e,0x0,0x29,0x29,0x29,0x0,0x69,0x29,0x1f,0x0,0x6b,0x2a,0x20,0x0,0x2e,0x2c,0x2c,0x0,0x6f,0x2b,0x21,0x0,0x2e,0x2d,0x2d,0x0,0x72,0x2c,0x22,0x0,0x2f,0x2e,0x2e,0x0,0x73,0x2d,0x22,0x0,0x30,0x2f,0x2f,0x0,0x75,0x2d,0x23,0x0,0x76,0x2e,0x23,0x0,0x30,0x30,0x30,0x0,0x79,0x2f,0x24,0x0,0x32,0x31,0x31,0x0,0x7a,0x2f,0x24,0x0,0x32,0x32,0x31,0x0,0x7b,0x30,0x25,0x0,0x7c,0x30,0x25,0x0,0x7d,0x30,0x25,0x0,0x7e,0x31,0x25,0x0,0x7f,0x31,0x26,0x0,0x36,0x35,0x35,0x0,0x83,0x33,0x27,0x0,0x87,0x34,0x28,0x0,0x37,0x37,0x37,0x0,0x89,0x35,0x29,0x0,0x8b,0x36,0x29,0x0,0x8c,0x36,0x2a,0x0,0x3a,0x39,0x39,0x0,0x8e,0x37,0x2a,0x0,0x90,0x38,0x2b,0x0,0x92,0x38,0x2b,0x0,0x3b,0x3b,0x3b,0x0,0x92,0x39,0x2b,0x0,0x93,0x39,0x2c,0x0,0x94,0x39,0x2c,0x0,0x3d,0x3c,0x3c,0x0,0x96,0x3a,0x2d,0x0,0x97,0x3a,0x2d,0x0,0x97,0x3b,0x2d,0x0,0x98,0x3b,0x2d,0x0,0x99,0x3b,0x2e,0x0,0x9a,0x3c,0x2e,0x0,0x9b,0x3c,0x2e,0x0,0x9c,0x3c,0x2e,0x0,0x9d,0x3d,0x2e,0x0,0x9d,0x3d,0x2f,0x0,0x9e,0x3d,0x2f,0x0,0x9f,0x3d,0x2f,0x0,0xa0,0x3e,0x2f,0x0,0xa0,0x3e,0x30,0x0,0xa1,0x3e,0x30,0x0,0xa2,0x3f,0x30,0x0,0xa3,0x3f,0x30,0x0,0x42,0x42,0x42,0x0,0xa4,0x3f,0x31,0x0,0xa4,0x40,0x31,0x0,0xa5,0x40,0x31,0x0,0x43,0x43,0x43,0x0,0x49,0x49,0x49,0x0,0x4a,0x49,0x49,0x0,0x4c,0x4b,0x4b,0x0,0x4d,0x4d,0x4d,0x0,0x54,0x54,0x54,0x0,0x57,0x57,0x57,0x0,0x58,0x58,0x58,0x0,0x59,0x59,0x59,0x0,0x5d,0x5d,0x5d,0x0,0x5f,0x5f,0x5f,0x0,0x64,0x64,0x64,0x0,0x65,0x65,0x65,0x0,0x67,0x67,0x67,0x0,0x6c,0x6c,0x6c,0x0,0x6e,0x6e,0x6e,0x0,0x70,0x70,0x70,0x0,0x74,0x74,0x74,0x0,0x79,0x79,0x79,0x0,0x7a,0x7a,0x7a,0x0,0x7d,0x7d,0x7d,0x0,0x7e,0x7e,0x7e,0x0,0x83,0x83,0x83,0x0,0x87,0x87,0x87,0x0,0x88,0x88,0x88,0x0,0x89,0x89,0x89,0x0,0x8c,0x8c,0x8c,0x0,0x8e,0x8e,0x8e,0x0,0x95,0x95,0x95,0x0,0x9f,0x9f,0x9f,0x0,0xa2,0xa2,0xa2,0x0,0xa4,0xa4,0xa4,0x0,0xa5,0xa5,0xa5,0x0,0xa6,0xa6,0xa6,0x0,0xa8,0xa8,0xa8,0x0,0xaa,0xaa,0xaa,0x0,0xab,0xab,0xab,0x0,0xae,0xae,0xae,0x0,0xb6,0xb6,0xb6,0x0,0xb8,0xb8,0xb8,0x0,0xb9,0xb9,0xb9,0x0,0xba,0xba,0xba,0x0,0xbb,0xbb,0xbb,0x0,0xbc,0xbc,0xbc,0x0,0xbd,0xbd,0xbd,0x0,0xc1,0xc1,0xc1,0x0,0xc2,0xc2,0xc2,0x0,0xc4,0xc4,0xc4,0x0,0xc5,0xc5,0xc5,0x0,0xc8,0xc8,0xc8,0x0,0xc9,0xc9,0xc9,0x0,0xca,0xca,0xca,0x0,0xcc,0xcc,0xcc,0x0,0xd1,0xd1,0xd1,0x0,0xd8,0xd8,0xd8,0x0,0xe1,0xd8,0xd6,0x0,0xd9,0xd9,0xd9,0x0,0xdb,0xdb,0xdb,0x0,0xe1,0xe1,0xe1,0x0,0xe2,0xe2,0xe2,0x0,0xe7,0xe7,0xe7,0x0,0xf4,0xe7,0xe5,0x0,0xe8,0xe8,0xe8,0x0,0xe9,0xe9,0xe9,0x0,0xea,0xea,0xea,0x0,0xee,0xee,0xee,0x0,0xef,0xef,0xef,0x0,0xf8,0xf0,0xef,0x0,0xf1,0xf1,0xf1,0x0,0xf4,0xf4,0xf4,0x0,0xf6,0xf6,0xf6,0x0,0xf7,0xf7,0xf7,0x0,0xf8,0xf8,0xf8,0x0,0xf9,0xf9,0xf9,0x0,0xfa,0xfa,0xfa,0x0,0xfb,0xfb,0xfb,0x0,0xfc,0xfc,0xfc,0x0,0xfd,0xfd,0xfd,0x0,0xfe,0xfe,0xfe,0x0,0xff,0xff,0xff,0x0,0x2d,0x9c,0x0,0x0,0x2d,0x9c,0x0,0x0,0x2d,0x9c,0x0,0x0,0x2d,0x9c,0x0,0x0,0xe,0x9c,0x1,0x98,0x17,0x8d,0x1,0x98,0x6,0x9c,0x0,0x0,0xe,0x9c,0x1,0x49,0x17,0x0,0x1,0x48,0x6,0x9c,0x0,0x0,0xe,0x9c,0x1,0x3f,0x1,0x47,0x15,0xb5,0x1,0x5a,0x1,0x31,0x6,0x9c,0x0,0x0,0xe,0x9c,0x0,0x3,0x51,0x2f,0xea,0x0,0x14,0xec,0x1,0x99,0x1,0x30,0x6,0x9c,0x0,0x0,0xe,0x9c,0x0,0x3,0x63,0x0,0xcf,0x0,0x14,0xec,0x1,0x9d,0x1,0x30,0x6,0x9c,0x0,0x0,0xe,0x9c,0x0,0x3,0x8f,0xe,0xa4,0x0,0x14,0xec,0x1,0x99,0x1,0x30,0x6,0x9c,0x0,0x0,0xf,0x9c,0x0,0x3,0x58,0x0,0xc1,0x0,0x13,0xec,0x1,0x7f,0x1,0x37,0x6,0x9c,0x0,0x0,0xf,0x9c,0x0,0x4,0x95,0x35,0x14,0xcc,0x12,0xec,0x1,0x69,0x1,0x40,0x6,0x9c,0x0,0x0,0xa,0x9c,0x1,0x9a,0x1,0x8e,0x4,0x9c,0x0,0x4,0x8c,0x22,0x2b,0xce,0x11,0xec,0x1,0x5d,0x1,0x46,0x6,0x9c,0x0,0x0,0x7,0x9c,0x0,0x7,0x9b,0x82,0x88,0x43,0x0,0x36,0x8a,0x0,0x3,0x9c,0x0,0x4,0x85,0x20,0x1f,0xce,0x10,0xec,0x1,0x3a,0x1,0x51,0x6,0x9c,0x0,0x0,0x6,0x9c,0x1,0x6d,0x1,0x1c,0x3,0x0,0x0,0x4,0x6e,0x1f,0x2a,0x90,0x3,0x9c,0x0,0x4,0x86,0x1d,0x42,0xd8,0xe,0xec,0x0,0x3,0xe8,0x6,0x58,0x0,0x6,0x9c,0x0,0x0,0x5,0x9c,0x0,0xb,0x82,0xd,0x72,0xb9,0xaf,0x0,0x50,0xc8,0x7,0x44,0x9a,0x0,0x3,0x9c,0x0,0x4,0x7e,0x11,0x6b,0xe5,0xd,0xec,0x0,0x3,0xd9,0x0,0x5f,0x0,0x6,0x9c,0x0,0x0,0x5,0x9c,0x0,0xc,0x5b,0x5,0xd8,0xec,0xd7,0x3,0x6,0xdc,0xb8,0x0,0x4a,0x93,0x3,0x9c,0x0,0x3,0x6c,0x0,0xb4,0x0,0xd,0xec,0x0,0x3,0xcf,0x0,0x6a,0x0,0x6,0x9c,0x0,0x0,0x5,0x9c,0x0,0xd,0x46,0x5d,0xec,0xeb,0xeb,0xc3,0xc4,0xec,0xec,0xb6,0x5,0x26,0x7c,0x0,0x3,0x9c,0x0,0x3,0x41,0x39,0xe4,0x0,0xc,0xec,0x0,0x3,0xbc,0x0,0x7d,0x0,0x6,0x9c,0x0,0x0,0x5,0x9c,0x0,0x6,0x3b,0x7b,0xe3,0x62,0x62,0xe3,0x4,0xec,0x0,0x9,0xc7,0x45,0xa,0x5f,0x9c,0x9c,0x74,0x0,0xbf,0x0,0xc,0xec,0x0,0x3,0xb2,0x4,0x96,0x0,0x6,0x9c,0x0,0x0,0x5,0x9c,0x0,0x6,0x52,0x24,0xd6,0x38,0x38,0xd7,0x5,0xec,0x0,0x8,0xdc,0x9f,0x0,0x51,0x97,0x9a,0x15,0xa8,0xc,0xec,0x1,0xa1,0x1,0x27,0x7,0x9c,0x0,0x0,0x5,0x9c,0x0,0x5,0x73,0x0,0xbb,0xcb,0xcb,0x0,0x7,0xec,0x0,0x7,0xeb,0xb0,0x0,0x3e,0x8f,0x3d,0x70,0x0,0xc,0xec,0x1,0x3c,0x1,0x4e,0x7,0x9c,0x0,0x0,0x5,0x9c,0x0,0x4,0x9b,0x28,0x67,0xeb,0xa,0xec,0x0,0x5,0xba,0xc,0x2e,0x4d,0x34,0x0,0xb,0xec,0x0,0x3,0xd3,0x0,0x61,0x0,0x7,0x9c,0x0,0x0,0x6,0x9c,0x0,0x3,0x64,0x0,0xc0,0x0,0xb,0xec,0x0,0x4,0xc5,0x13,0x1b,0xb,0xb,0xec,0x0,0x3,0xb7,0x1,0x82,0x0,0x7,0x9c,0x0,0x0,0x6,0x9c,0x0,0x4,0x9a,0x26,0x60,0xe9,0xb,0xec,0x0,0x3,0xc2,0x3,0x4,0x0,0xb,0xec,0x1,0x87,0x1,0x2d,0x8,0x9c,0x0,0x0,0x7,0x9c,0x0,0x3,0x66,0x0,0xbc,0x0,0xc,0xec,0x0,0x3,0xae,0x0,0xd2,0x0,0x9,0xec,0x0,0x3,0xd3,0x3,0x5c,0x0,0x8,0x9c,0x0,0x0,0x7,0x9c,0x0,0x4,0x9b,0x2d,0x57,0xe5,0xb,0xec,0x0,0x3,0xe1,0x1e,0xab,0x0,0x9,0xec,0x0,0x3,0xac,0x8,0x89,0x0,0x8,0x9c,0x0,0x0,0x8,0x9c,0x0,0x3,0x6f,0x0,0xb5,0x0,0xc,0xec,0x1,0x83,0x1,0xa1,0x8,0xec,0x0,0x3,0xd8,0x12,0x4f,0x0,0x9,0x9c,0x0,0x0,0x9,0x9c,0x0,0x7,0x41,0x1f,0xdb,0xea,0xa6,0xaa,0xe9,0x0,0x7,0xec,0x1,0xca,0x1,0xd0,0x8,0xec,0x0,0x3,0xa3,0x9,0x84,0x0,0x9,0x9c,0x0,0x0,0x9,0x9c,0x0,0x7,0x80,0x8,0xa9,0xdf,0x3,0x0,0xb3,0x0,0x10,0xec,0x0,0x3,0xbd,0x0,0x59,0x0,0xa,0x9c,0x0,0x0,0xa,0x9c,0x0,0x7,0x55,0x5,0xd1,0x9e,0x0,0x33,0xe7,0x0,0xe,0xec,0x0,0x4,0xcd,0x18,0x35,0x98,0xa,0x9c,0x0,0x0,0xa,0x9c,0x0,0x7,0x8e,0x17,0x78,0xd5,0x33,0x23,0xe2,0x0,0x5,0xec,0x1,0xeb,0x7,0xec,0x0,0x4,0xc6,0x24,0x21,0x8b,0xb,0x9c,0x0,0x0,0xb,0x9c,0x0,0x5,0x68,0x4,0xaa,0xdd,0xd8,0x0,0x6,0xec,0x1,0xe0,0x5,0xec,0x0,0x5,0xe5,0xb1,0x7,0x2c,0x85,0x0,0xc,0x9c,0x0,0x0,0xc,0x9c,0x0,0x3,0x56,0x3,0xd0,0x0,0x7,0xec,0x1,0xda,0x3,0xec,0x0,0x6,0xe1,0xb9,0x54,0x2,0x4c,0x91,0xd,0x9c,0x0,0x0,0xc,0x9c,0x0,0x7,0x92,0xd,0xad,0xec,0xe2,0xde,0xe6,0x0,0x3,0xec,0x0,0x8,0xd4,0xc9,0xb6,0xa0,0x12,0x0,0x32,0x71,0xf,0x9c,0x0,0x0,0xc,0x9c,0x0,0x10,0x91,0x10,0xa7,0xc6,0x7,0x0,0x7,0xcc,0xec,0xa5,0xf,0x0,0x0,0x21,0x53,0x79,0x11,0x9c,0x0,0x0,0xc,0x9c,0x0,0xd,0x76,0x0,0xbe,0x4b,0x25,0x5b,0x1a,0x72,0xe6,0x65,0x29,0x73,0x8b,0x0,0x14,0x9c,0x0,0x0,0xc,0x9c,0x0,0xb,0x71,0x0,0x39,0x9,0x7a,0x9c,0x68,0x2,0xa2,0x19,0x55,0x0,0x16,0x9c,0x0,0x0,0xc,0x9c,0x0,0x4,0x81,0x16,0x16,0x75,0x3,0x9c,0x0,0x4,0x5e,0x4,0x1,0x77,0x16,0x9c,0x0,0x0,0xd,0x9c,0x1,0x94,0x1,0x97,0x5,0x9c,0x1,0x77,0x1,0x74,0x17,0x9c,0x0,0x0,0x2d,0x9c,0x0,0x0,0x2d,0x9c,0x0,0x0,0x2d,0x9c,0x0,0x0,0x2d,0x9c,0x0,0x0,0x2d,0x9c,0x0,0x0,0x2d,0x9c,0x0,0x1};
#endif

const uint8_t* KNIGHT() {
	return KNIGHT_DATA;
}

const uint32_t KNIGHT_SIZE() {
	return sizeof(KNIGHT_DATA);
}