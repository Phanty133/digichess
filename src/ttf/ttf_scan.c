#include "ttf/ttf_scan.h"

static void calc_midpoint(
	int16_t* x, int16_t* y,
	int16_t x0, int16_t y0,
	int16_t x1, int16_t y1
) {
	*x = ((x1 + x0) >> 1);
	*y = ((y1 + y0) >> 1);
}

static uint8_t ray_intersects_line(
	int16_t x, int16_t y,
	int16_t x0, int16_t y0,
	int16_t x1, int16_t y1
) {
	if (y0 >= y || y1 < y) return 0;

	if (y == y0 && x > x0) return 1;
	if (y == y1 && x > x1) return 1;

	float inv_slope = (float)(x1 - x0) / (y1 - y0);

	return (inv_slope * (y - y0) + x0) <= x;
}

static uint8_t ray_intersects_curve(
	int16_t x, int16_t y,
	int16_t x0, int16_t y0,
	int16_t x1, int16_t y1,
	int16_t x2, int16_t y2
) {
	if (y0 >= y || y2 < y) return 0;

	if (y == y0 && x > x0) return 1;
	if (y == y2 && x > x2) return 1;

	float t;
	int16_t a = y0 - y1 * 2 + y2;

	if (a == 0) {
		if (y1 == y2) return 0;

		int16_t t_top = y - y1 * 2 + y2;
		int16_t t_bot = (y1 - y2) * 2;

		t = (float)(-t_top) / t_bot;
	} else {
		float root = sqrtf_16b(y1 * y1 - y0 * y2 + y * a);
		float t_div_top = y0 - y1 + root;
		t = t_div_top / a;
	}

	if (t < 0 || t > 1) return 0;

	float rev_t = 1 - t;
	int16_t x_c = x1 + rev_t * rev_t * (x0 - x1) + t * t * (x2 - x1);

	return (x_c + 0) <= x; // No idea why, but the x seems to be off by 1 pixel
}

static void transform_points(
	TTF_Point* points,
	uint16_t num_points,
	float scale,
	int16_t x_offset,
	int16_t y_offset,
	uint16_t height
) {
	for (int i = 0; i < num_points; i++) {
		TTF_Point* p = &points[i];

		p->x *= scale;
		p->y *= scale * -1;

		p->x += x_offset;
		p->y += height - y_offset;
	}
}

void gen_char_fill(
	Bitmap8* bitmap,
	const uint8_t* font,
	char charcode,
	float scale,
	int bitmap_offset_x,
	int bitmap_offset_y
) {
	TTF_cmapSubtableFormat4* subtable = ttf_get_cmap_subtable(font);
	int glyph_id = ttf_get_glyph_id(subtable, charcode);
	TTF_glyfHead* glyf_head = ttf_get_char_glyf(font, glyph_id);

	int num_contours = ttf_get_contour_count(glyf_head);
	uint16_t contour_points[num_contours];
	ttf_get_contour_end_points(glyf_head, contour_points);

	uint16_t num_points = ttf_get_total_points(glyf_head);
	TTF_Point points[num_points];

	ttf_read_simple_glyph(font, glyph_id, points);
	transform_points(points, num_points, scale, bitmap_offset_x, bitmap_offset_y, bitmap->height);

	for (int y = 0; y < bitmap->height; y++) {
		for (int x = bitmap_offset_x; x < bitmap->width; x++) {
			int cross_counter = 0;

			for (int i = 0; i < num_points; i++) {
				TTF_Point* p0 = &points[i];
				TTF_Point* p1 = p0->next;

				if (p0->on_curve && p1->on_curve) {
					// Segment is a line
					if (ray_intersects_line(x, y, p0->x, p0->y, p1->x, p1->y)) {
						cross_counter--;
					} else if (ray_intersects_line(x, y, p1->x, p1->y, p0->x, p0->y)) {
						cross_counter++;
					}

					continue;
				}

				// Segment is a curve

				TTF_Point* p2 = p1->next;

				// Possible cases:
				// 1. p0 is on curve, p1 is off curve, and p2 is on curve -> simple bezier
				// 2. p0 is on curve, p1 is off curve, and p2 is off curve -> inferred point between p1 and p2
				// 3. p0 is off curve, p1 is on curve -> skip
				// 4. p0 is off curve, p1 is off curve -> inferred point between p0 and p1

				uint16_t p0x, p0y;
				uint16_t p1x, p1y;
				uint16_t p2x, p2y;

				if (p0->on_curve) {
					p0x = p0->x;
					p0y = p0->y;
					p1x = p1->x;
					p1y = p1->y;

					if (p2->on_curve) {
						p2x = p2->x;
						p2y = p2->y;
					} else {
						// Inferred point between p1 and p2
						calc_midpoint(&p2x, &p2y, p1->x, p1->y, p2->x, p2->y);
					}
				} else {
					// Skip if it's a regular control point
					if (p1->on_curve) continue;

					// Proceed if it's the first of 2 control points that form an
					// inferred on-curve point.
					// Inferred point between p0 and p1
					calc_midpoint(&p0x, &p0y, p0->x, p0->y, p1->x, p1->y);

					p1x = p1->x;
					p1y = p1->y;
					p2x = p2->x;
					p2y = p2->y;
				}

				if (ray_intersects_curve(x, y, p0x, p0y, p1x, p1y, p2x, p2y)) {
					cross_counter--;
				} else if (ray_intersects_curve(x, y, p2x, p2y, p1x, p1y, p0x, p0y)) {
					cross_counter++;
				}
			}

			if (cross_counter != 0) {
				bitmap->data[y * bitmap->width + x + bitmap_offset_x] = 1;
			}
		}
	}
}

void gen_char_outline(
	Bitmap8* bitmap,
	const uint8_t* font,
	char charcode,
	float scale,
	int bitmap_offset_x,
	int bitmap_offset_y
) {
	TTF_cmapSubtableFormat4* subtable = ttf_get_cmap_subtable(font);
	int glyph_id = ttf_get_glyph_id(subtable, charcode);
	TTF_glyfHead* glyf_head = ttf_get_char_glyf(font, glyph_id);

	int num_contours = ttf_get_contour_count(glyf_head);
	uint16_t contour_points[num_contours];
	ttf_get_contour_end_points(glyf_head, contour_points);

	uint16_t num_points = ttf_get_total_points(glyf_head);
	TTF_Point points[num_points];

	ttf_read_simple_glyph(font, glyph_id, points);
	transform_points(points, num_points, scale, bitmap_offset_x, bitmap_offset_y, bitmap->height);

	// Mark outline points
	for (int i = 0; i < num_points; i++) {
		TTF_Point* p = &points[i];
		int16_t cell = p->y * bitmap->width + p->x + bitmap_offset_x;

		if (p->on_curve) {
			bitmap->data[cell] = 2;
		} else {
			bitmap->data[cell] = 3;
		}
	}
}
