#ifndef __TTF_GLYPHREAD_H
#define __TTF_GLYPHREAD_H

#include "memory.h"
#include "ttf/ttf_structs.h"
#include "ttf/ttf_funcs.h"
#include "uart.h"

/// @brief Gets the number of contours in the glyph
/// @param glyf_head The glyf table head pointer for the glyph
/// @return Number of contours
uint16_t ttf_get_contour_count(TTF_glyfHead* glyf_head);

/// @brief Gets the contour end point indices
/// @param glyf_head The glyf table head pointer for the glyph
/// @param contours_buf Buffer for the end point indices. Must be allocated large enough for the number of contours.
void ttf_get_contour_end_points(TTF_glyfHead* glyf_head, uint16_t* contours_buf);

/// @brief Gets the number of points on each contour
/// @param glyf_head The glyf table head pointer for the glyph
/// @param buf Buffer for the point counts. Must be allocated large enough for the number of contours.
void ttf_calc_points_per_contour(TTF_glyfHead* glyf_head, uint16_t* buf);

/// @brief Gets the total number of points in the glyph
/// @param glyf_head The glyf table head pointer for the glyph
/// @return The number of points on the glyph
uint16_t ttf_get_total_points(TTF_glyfHead* glyf_head);

/// @brief Gets the address for the flag array in the glyf data table
/// @param glyf_head The glyf table head pointer for the glyph
/// @return Address of the flag array
uint8_t* ttf_get_flag_start(TTF_glyfHead* glyf_head);

/// @brief Parses the flag for each point using the glyf table's flag array.
/// @param glyf_head The glyf table head pointer for the glyph
/// @param points Point data buffer. Must be allocated large enough for the number of points in the glyph.
/// @return Size of the flag array
uint16_t ttf_parse_glyph_flags(TTF_glyfHead* glyf_head, TTF_Point* points);

/// @brief Parses the x coordinate for each point using the glyf table's x array. The points must have flag data parsed.
/// @param glyf_head The glyf table head pointer for the glyph
/// @param offset Offset from the flag array address
/// @param points Point data buffer. Must be allocated large enough for the number of points in the glyph.
/// @return Size of the X coordinate array
uint16_t ttf_parse_glyph_coords_x(TTF_glyfHead* glyf_head, uint16_t offset, TTF_Point* points);

/// @brief Parses the y coordinate for each point using the glyf table's y array. The points must have flag data parsed.
/// @param glyf_head The glyf table head pointer for the glyph
/// @param offset Offset from the flag array address
/// @param points Point data buffer. Must be allocated large enough for the number of points in the glyph.
/// @return Size of the Y coordinate array
uint16_t ttf_parse_glyph_coords_y(TTF_glyfHead* glyf_head, uint16_t offset, TTF_Point* points);

/// @brief Count the number of pointes omitted by two sequential bezier control points
/// @param points Point data buffer. Must have flag and coordinate data populated.
/// @param point_count Number of points in the points array
/// @return The number of points omitted
uint16_t ttf_count_skipped_points(TTF_Point* points, uint16_t point_count);

/// @brief Creates linked lists between each contour
/// @param points Point data buffer. Must have the countour_index index field populated (ttf_parse_glyph_flags()).
/// @param point_count Number of points in the points array
void ttf_set_next_point_ref(TTF_Point* points, uint16_t point_count);

/// @brief Reads The point data for a glyph
/// @param font Font TTF data to use
/// @param glyph_id The glyph ID to read (ttf_get_glyph_id())
/// @param out_points Point data buffer. Must be allocated large enough for the number of points in the glyph.
void ttf_read_simple_glyph(const uint8_t* font, uint16_t glyph_id, TTF_Point* out_points);

#endif