#ifndef __TTF_GLYPHREAD_H
#define __TTF_GLYPHREAD_H

#include "memory.h"
#include "ttf/ttf_structs.h"
#include "ttf/ttf_funcs.h"
#include "uart.h"

uint16_t ttf_get_contour_count(TTF_glyfHead* glyf_head);
void ttf_get_contour_end_points(TTF_glyfHead* glyf_head, uint16_t* contours_buf);
void ttf_calc_points_per_contour(TTF_glyfHead* glyf_head, uint16_t* buf);
uint16_t ttf_get_total_points(TTF_glyfHead* glyf_head);

uint8_t* ttf_get_flag_start(TTF_glyfHead* glyf_head);
uint16_t ttf_parse_glyph_flags(TTF_glyfHead* glyf_head, TTF_Point* points);
uint16_t ttf_parse_glyph_coords_x(TTF_glyfHead* glyf_head, uint16_t offset, TTF_Point* points);
uint16_t ttf_parse_glyph_coords_y(TTF_glyfHead* glyf_head, uint16_t offset, TTF_Point* points, const uint8_t* font);

uint16_t ttf_count_skipped_points(TTF_Point* points, uint16_t point_count);
void ttf_set_next_point_ref(TTF_Point* points, uint16_t point_count);

void ttf_read_simple_glyph(
	const uint8_t* font,
	uint16_t glyph_id,
	TTF_Point* out_points
);

#endif