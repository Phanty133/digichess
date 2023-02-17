/// @file bmp_funcs.h
/// @brief BMP helper functions

#ifndef __BMP_FUNCS_H
#define __BMP_FUNCS_H

#include "math.h"
#include "bmp_structs.h"

/// @brief Get the header of a BMP file
/// @param file BMP data byte array
/// @return Pointer to the BMP header
const BMP_Header* bmp_get_header(const uint8_t* file);

/// @brief Get the size of the info header in a BMP file
/// @param file BMP data byte array
/// @return Size of the info header
const uint32_t bmp_get_info_header_size(const uint8_t* file);

/// @brief Get the info header of a BMP file
/// @param file BMP data byte array
/// @return Pointer to the BMP info header
const BMP_InfoHeader* bmp_get_info(const uint8_t* file);

/// @brief Get the color table of a BMP file
/// @param file BMP data byte array
/// @return Pointer to the start of the color table
const BMP_Color* bmp_get_color_table(const uint8_t* file);

/// @brief Get the size of a BMP color table
/// @param file BMP data byte array
/// @return The size of the color table
const uint16_t bmp_get_color_table_size(const uint8_t* file);

/// @brief Get the compression method of a BMP file
/// @param file BMP data byte array
/// @return Compression method used
const BMP_Compression bmp_get_compression(const uint8_t* file);

/// @brief Calculates the packed row size in a BMP file
/// @param file BMP data byte array
/// @return Row size
const uint32_t bmp_get_row_size(const uint8_t* file);

/// @brief Finds the start of BMP image data
/// @param file BMP data byte array
/// @return Pointer to the start of the image data
const uint8_t* bmp_get_image_data(const uint8_t* file);

#endif