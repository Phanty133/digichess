#ifndef __TTF_FUNCS_H
#define __TTF_FUNCS_H

#include <stdint.h>
#include "ttf/ttf_structs.h"
#include "ttf/ttf_glyphread.h"

/// @brief Reads a big-endian uint32_t and returns it little-endian 
/// @param uint_big Big-endian uint32
/// @return Little-endian uint32
uint32_t get_uint32_little(uint32_t uint_big);

/// @brief Reads a big-endian uint16_t and returns it little-endian 
/// @param uint_big Big-endian uint16
/// @return Little-endian uint16
uint16_t get_uint16_little(uint16_t uint_big);

/// @brief Reads a big-endian int32 and returns it little-endian 
/// @param uint_big Big-endian int32
/// @return Little-endian int32
int32_t get_int32_little(int32_t int_big);

/// @brief Reads a big-endian int16_t and returns it little-endian 
/// @param uint_big Big-endian int16
/// @return Little-endian int16
int16_t get_int16_little(int16_t int_big);

/// @brief Returns a pointer to a TTF table
/// @param font Font TTF data
/// @param table_tag The tag corresponding to the table
/// @return TTF table pointer
const void* ttf_get_table(const uint8_t* font, uint32_t table_tag);

/// @brief Check if the encoding record has a format 4 subtable
/// @param record Address to a TTF cmap encoding record
/// @return True if the record points to a format 4 subtable
int ttf_is_platform_valid(TTF_cmapEncodingRecord* record);

/// @brief Returns a format 4 cmap subtable from the font
/// @param font TTF file data
/// @return Address to the format 4 cmap subtable in the font data
TTF_cmapSubtableFormat4* ttf_get_cmap_subtable(const uint8_t* font);

/// @brief Returns the glyph ID corresponding to the charcode from a cmap format 4 subtable
/// @param subtable Pointer to the start of the subtable
/// @param charcode The character code to search for
/// @return Glyph ID corresponding to charcode
uint16_t ttf_get_glyph_id(TTF_cmapSubtableFormat4* subtable, char charcode);

/// @brief Gets the glyf data table corresponding to a glyph ID
/// @param font Pointer to the TTF font data
/// @param glyph_id Glyph ID obtained from a cmap subtable
/// @return glyf data table pointer
TTF_glyfHead* ttf_get_char_glyf(const uint8_t* font, uint16_t glyph_id);

/// @brief Gets the hmtx metric data corresponding to a glyph ID
/// @param font Pointer to the TTF font data
/// @param glyph_id Glyph ID obtained from a cmap subtable
/// @return hmtx metric data pointer
TTF_hmtxLongHorMetric* ttf_get_char_hmtx(const uint8_t* font, uint16_t glyph_id);

/// @brief Gets the dimensions and spacing of a character
/// @param font Pointer to the TTF font data
/// @param charcode ASCII character code
/// @return Dimensions and spacing in FUnits
TTF_CharDims ttf_get_char_dims(const uint8_t* font, char charcode);

/// @brief Gets the dimensions and spacing of a character and scales it
/// @param font Pointer to the TTF font data
/// @param charcode ASCII character code
/// @param scale FUnits to pixels scaling factor
/// @return Dimensions and spacing in pixels
TTF_CharDims ttf_get_char_dims_scaled(const uint8_t* font, char charcode, float scale);

/// @brief Calculates the FUnit to pixel scaling factor
/// @param font Pointer to the TTF font data
/// @param font_size_pt Font size in points (pt)
/// @param screen_ppi Screen pixels per inch (ppi/dpi)
/// @return Scaling factor in pixels per FUnit
float ttf_get_scale(const uint8_t* font, uint16_t font_size_pt, uint16_t screen_ppi);

#endif