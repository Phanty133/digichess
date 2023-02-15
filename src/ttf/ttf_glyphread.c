#include "ttf/ttf_glyphread.h"

uint16_t ttf_get_contour_count(TTF_glyfHead* glyf_head) {
	return get_uint16_little(glyf_head->number_of_contours);
}

void ttf_get_contour_end_points(TTF_glyfHead* glyf_head, uint16_t* contours_buf) {
	TTF_glyfBody* glyf_body = (TTF_glyfBody*)(glyf_head + 1);

	uint16_t contours_num = ttf_get_contour_count(glyf_head);
	uint16_t* contours_end_points_big = &glyf_body->end_pts_of_contours;

	for (int i = 0; i < contours_num; i++) {
		contours_buf[i] = get_uint16_little(contours_end_points_big[i]);
	}
}

void ttf_calc_points_per_contour(TTF_glyfHead* glyf_head, uint16_t* buf) {
	uint16_t contours_num = ttf_get_contour_count(glyf_head);
	uint16_t contours_buf[contours_num];

	ttf_get_contour_end_points(glyf_head, contours_buf);

	for (int i = 0; i < contours_num; i++) {
		int end_point = get_uint16_little(contours_buf[i]);
		
		buf[i] = i == 0 ? end_point : (end_point - buf[i - 1]);
	}
}

uint16_t ttf_get_total_points(TTF_glyfHead* glyf_head) {
	uint16_t contours_num = get_uint16_little(glyf_head->number_of_contours);
	uint16_t contours_end_points[contours_num];

	ttf_get_contour_end_points(glyf_head, contours_end_points);
	return contours_end_points[contours_num - 1] + 1;
}

uint8_t* ttf_get_flag_start(TTF_glyfHead* glyf_head) {
	TTF_glyfBody* glyf_body = (TTF_glyfBody*)(glyf_head + 1);
	uint16_t contours_num = get_uint16_little(glyf_head->number_of_contours);

	// The instruction length is right after the contour end points
	uint16_t* instr_len_ptr = (&glyf_body->end_pts_of_contours) + contours_num;
	uint16_t instr_len = get_uint16_little(*instr_len_ptr);

	// The instructions array is right after the instruction length
	uint8_t* instr = (uint8_t*)(instr_len_ptr + 1);

	return instr + instr_len;
}

uint16_t ttf_parse_glyph_flags(TTF_glyfHead* glyf_head, TTF_Point* points) {
	uint16_t contours_num = get_uint16_little(glyf_head->number_of_contours);
	uint16_t contours_end_points[contours_num];

	ttf_get_contour_end_points(glyf_head, contours_end_points);

	uint16_t total_points = ttf_get_total_points(glyf_head);
	uint8_t* flags_start = ttf_get_flag_start(glyf_head);
	uint8_t* cur_flag = flags_start;
	int repeat_count = 0;

	int cur_contour = 0;
	uint8_t next_is_start = 1;

	for (int i = 0; i < total_points; i++) {
		uint8_t flag = *cur_flag;

		TTF_Point* p = &points[i];
		p->flag = flag;
		p->on_curve = flag & TTF_GLYF_ON_CURVE_POINT;

		// Check if the point is the start or end of a contour
		p->is_contour_start = 0;
		p->is_contour_end = 0;

		if (next_is_start) {
			p->is_contour_start = 1;
			next_is_start = 0;

			if (i != 0) cur_contour++;
		} else if (
			(cur_contour == 0 && i == contours_end_points[0])
			|| (cur_contour != 0 && i == contours_end_points[cur_contour])
		) {
			p->is_contour_end = 1;
			next_is_start = 1;
		}

		if (cur_contour == 0) {
			p->contour_index = i;
		} else {
			p->contour_index = i - contours_end_points[cur_contour - 1] - 1;
		}

		p->contour = cur_contour;

		// Handle flag repeats

		uint8_t flag_repeat = (flag & TTF_GLYF_REPEAT);

		if (repeat_count > 0) {
			repeat_count--;
		} else if (flag_repeat) {
			repeat_count = *(cur_flag + 1);
		} else {
			cur_flag++;
		}

		if (repeat_count == 0 && flag_repeat) {
			cur_flag += 2;
		}
	}

	return cur_flag - flags_start;
}

uint16_t ttf_parse_glyph_coords_x(TTF_glyfHead* glyf_head, uint16_t offset, TTF_Point* points) {
	uint16_t total_points = ttf_get_total_points(glyf_head);

	uint8_t* flag_start = ttf_get_flag_start(glyf_head);
	uint8_t* x_start = flag_start + offset;
	uint8_t* cur_x = x_start;

	for (int i = 0; i < total_points; i++) {
		TTF_Point* p = &points[i];

		// X_SHORT=0, X_IS_SAME=0 -> Coordinate is 16-bit
		// X_SHORT=0, X_IS_SAME=1 -> Coordinate is equal to the previous point's coordinate
		// X_SHORT=1, X_IS_SAME=0 -> Coordinate is 8 bit and is negative
		// X_SHORT=1, X_IS_SAME=1 -> Coordinate is 8 bit and is positive
		uint8_t x_short = p->flag & TTF_GLYF_X_SHORT_VECTOR;
		uint8_t x_is_same = p->flag & TTF_GLYF_X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR;

		if (x_short) {
			// coordinate is uint8 and x_is_same is sign
			p->x = ((int16_t)*cur_x) * (x_is_same ? 1 : -1);
			cur_x++;
		} else if (x_is_same) {
			// Coordinate repeated
			p->x = points[i - 1].x;
		} else {
			// coordinate is int16

			// I first create an int16_t, whose bytes I set individually with
			// the cur_ pointer. GOD FORBID I first cast cur_x into an int16_t*
			// and dereference that. Then God shall smite thee.

			int16_t x_2bit;
			uint8_t* x_2bit_ptr = (uint8_t*)(&x_2bit);
			*x_2bit_ptr = *cur_x;
			*(x_2bit_ptr + 1) = *(cur_x + 1);

			p->x = get_int16_little(x_2bit);
			cur_x += 2;
		}

		if (i != 0 && !(!x_short && x_is_same)) {
			// If not the first point and not a repeated coordinate,
			// add the previous point's coordinate, as the coordinates
			// of every next point is relative to the previous point

			p->x += points[i - 1].x;
		}
	}

	return cur_x - x_start;
}

uint16_t ttf_parse_glyph_coords_y(TTF_glyfHead* glyf_head, uint16_t offset, TTF_Point* points) {
	uint16_t total_points = ttf_get_total_points(glyf_head);

	uint8_t* flag_start = ttf_get_flag_start(glyf_head);
	uint8_t* y_start = flag_start + offset;
	uint8_t* cur_y = y_start;

	for (int i = 0; i < total_points; i++) {
		TTF_Point* p = &points[i];
		TTF_Point* prev_p = &points[i - 1];

		uint8_t y_short = p->flag & TTF_GLYF_Y_SHORT_VECTOR;
		uint8_t y_is_same = p->flag & TTF_GLYF_Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR;

		if (y_short) {
			// coordinate is uint8 and y_is_same is sign
			p->y = (*cur_y) * (y_is_same ? 1 : -1);
			cur_y++;
		} else if (y_is_same) {
			// Coordinate repeated
			p->y = prev_p->y;
		} else {
			// coordinate is int16

			// Appeasement of the gods. See explanation in the similar case in the
			// ttf_parse_glyph_coords_x function.
			int16_t y_2bit;
			uint8_t* y_2bit_ptr = (uint8_t*)(&y_2bit);
			*y_2bit_ptr = *cur_y;
			*(y_2bit_ptr + 1) = *(cur_y + 1);

			p->y = get_int16_little(y_2bit);
			cur_y += 2;
		}

		if (i != 0 && !(!y_short && y_is_same)) {
			// If not the first point and not a repeated coordinate,
			// add the previous point's coordinate, as the coordinates
			// of every next point is relative to the previous point

			p->y += prev_p->y;
		}
	}

	return cur_y - y_start;
}

uint16_t ttf_count_skipped_points(TTF_Point* points, uint16_t point_count) {
	uint16_t skipped = 0;
	
	for (int i = 1; i < point_count; i++) {
		if (points[i - 1].on_curve || points[i].on_curve) continue;

		skipped++;
	}

	return skipped;
}

void ttf_set_next_point_ref(TTF_Point* points, uint16_t point_count) {
	for (int i = 0; i < point_count; i++) {
		TTF_Point* p = &points[i];

		if (p->is_contour_end) {
			p->next = &points[i - p->contour_index];
		} else {
			p->next = &points[i + 1];
		}
	}
}

// TODO: Parse instructions
void ttf_read_simple_glyph(
	const uint8_t* font,
	uint16_t glyph_id,
	TTF_Point* out_points
) {
	TTF_glyfHead* glyf_head = ttf_get_char_glyf(font, glyph_id);
	uint16_t total_points = ttf_get_total_points(glyf_head);
	
	// Allocate memory for points
	uint16_t flags_size = ttf_parse_glyph_flags(glyf_head, out_points);
	uint16_t x_size = ttf_parse_glyph_coords_x(glyf_head, flags_size, out_points);
	uint16_t y_size = ttf_parse_glyph_coords_y(glyf_head, flags_size + x_size, out_points);
	ttf_set_next_point_ref(out_points, total_points);
}
