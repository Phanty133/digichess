#include "ttf/ttf_funcs.h"

uint32_t get_uint32_little(uint32_t uint_big) {
	return ((uint_big >> 24) & 0xff) // B3 to B0
	| ((uint_big << 8) & 0xff0000) // B1 to B2
	| ((uint_big >> 8) & 0xff00) // B2 to B1
	| ((uint_big << 24) & 0xff000000); // B0 to B3
}

uint16_t get_uint16_little(uint16_t uint_big) {
	return (uint_big >> 8) | (uint_big << 8);
}

int32_t get_int32_little(int32_t int_big) {
	uint32_t uint_big = (uint32_t)int_big; // First cast to an unsigned to prevent overflows

	return (int32_t)((uint_big >> 24) & 0xff) // B3 to B0
	| ((uint_big << 8) & 0xff0000) // B1 to B2
	| ((uint_big >> 8) & 0xff00) // B2 to B1
	| ((uint_big << 24) & 0xff000000); // B0 to B3
}

int16_t get_int16_little(int16_t int_big) {
	uint16_t uint_big = (uint16_t)int_big; // First cast to an unsigned to prevent overflows

	return (int16_t)((uint_big >> 8) | (uint_big << 8));
}

const void* ttf_get_table(const uint8_t* font, uint32_t table_tag) {
	TableDirectory* dir = (TableDirectory*)font;
	uint16_t num_tables = get_uint16_little(dir->num_tables);

	for (int i = 0; i < num_tables; i++) {
		TableRecord table = dir->table_records[i];
		Tag tag = table.table_tag;

		if (tag != table_tag) continue;

		return font + get_uint32_little(table.offset);
	}

	return 0; // Return nullptr if not found
}

int ttf_is_platform_valid(TTF_cmapEncodingRecord* record) {
	uint16_t pid = get_uint16_little(record->platform_id);
	uint16_t enc_id = get_uint16_little(record->encoding_id);

	return (
		(pid == 3 && (enc_id == 0 || enc_id == 1 || enc_id == 10))
		|| (pid == 0 && (enc_id >= 0 && enc_id <= 4))
	);
}

TTF_cmapSubtableFormat4* ttf_get_cmap_subtable(const uint8_t* font) {
	TTF_cmap* cmap = (TTF_cmap*)ttf_get_table(font, TTF_TABLE_CMAP);
	uint16_t cmap_num_tables = get_uint16_little(cmap->num_tables);

	for (int i = 0; i < cmap_num_tables; i++) {
		TTF_cmapEncodingRecord* record = &(cmap->encoding_records[i]);

		if (!ttf_is_platform_valid(record)) continue;

		return (TTF_cmapSubtableFormat4*)((uint8_t*)cmap + get_uint32_little(record->offset));
	}

	return 0; // nullptr if no format 4 subtable found
}

uint16_t ttf_get_glyph_id(TTF_cmapSubtableFormat4* subtable, char charcode) {
	uint16_t seg_count = get_uint16_little(subtable->seg_count_x2) >> 1;
	uint32_t seg_array_offset = sizeof(uint16_t) * seg_count;

	uint8_t* end_offset = (uint8_t*)&subtable->end_code;

	// +2 for the start_offset to adjust for reserved_pad
	uint8_t* start_offset = end_offset + seg_array_offset + 2;

	for (int i = 0; i < seg_count; i++) {
		uint16_t end = get_uint16_little(((uint16_t*)end_offset)[i]);

		if (charcode > end) continue;

		uint16_t start = get_uint16_little(((uint16_t*)start_offset)[i]);

		if (start > charcode) continue; // Shouldn't happen, but just in case

		uint8_t* id_delta_offset = start_offset + seg_array_offset;
		uint8_t* id_range_offset = id_delta_offset + seg_array_offset;
			
		uint16_t id_delta = get_uint16_little(((uint16_t*)id_delta_offset)[i]);
		uint16_t id_range = get_uint16_little(((uint16_t*)id_range_offset)[i]);

		if (id_range == 0) return (charcode + id_delta) & 0xffff;

		return *(
			(id_range >> 1)
			+ (charcode - start)
			+ &((uint16_t*)id_range_offset)[i]
		);
	}

	return 0;
}

TTF_glyfHead* ttf_get_char_glyf(const uint8_t* font, uint16_t glyph_id) {
	TTF_head* head = (TTF_head*)ttf_get_table(font, TTF_TABLE_HEAD);
	const void* loca_offset = ttf_get_table(font, TTF_TABLE_LOCA);
	Offset32 glyf_offset;

	if (head->index_to_loc_format == 0) {
		TTF_locaShort* loca = (TTF_locaShort*)loca_offset;
		glyf_offset = (get_uint16_little(*(&loca->offsets + glyph_id)) << 1);
	} else {
		TTF_locaLong* loca = (TTF_locaLong*)loca_offset;
		glyf_offset = get_uint32_little(*(&loca->offsets + glyph_id));
	}

	uint8_t* glyf_start = (uint8_t*)ttf_get_table(font, TTF_TABLE_GLYF);

	return (TTF_glyfHead*)(glyf_start + glyf_offset);
}

TTF_hmtxLongHorMetric* ttf_get_char_hmtx(const uint8_t* font, uint16_t glyph_id) {
	TTF_hmtx* hmtx = (TTF_hmtx*)ttf_get_table(font, TTF_TABLE_HMTX);
	
	return &hmtx->h_metrics + glyph_id;
}

TTF_CharDims ttf_get_char_dims(const uint8_t* font, char charcode) {
	TTF_cmapSubtableFormat4* subtable = ttf_get_cmap_subtable(font);

	// TODO: Handle case where there is no format 4 subtable

	uint16_t glyph_id = ttf_get_glyph_id(subtable, charcode);
	TTF_glyfHead* glyf = ttf_get_char_glyf(font, glyph_id);
	TTF_hmtxLongHorMetric* hmtx = ttf_get_char_hmtx(font, glyph_id);

	TTF_CharDims spacing;
	spacing.x = get_int16_little(glyf->x_min);
	spacing.y = get_int16_little(glyf->y_min);
	spacing.max_x = get_int16_little(glyf->x_max);
	spacing.max_y = get_int16_little(glyf->y_max);
	spacing.width = spacing.max_x - spacing.x;
	spacing.height = spacing.max_y - spacing.y;
	spacing.lsb = get_int16_little(hmtx->lsb);
	spacing.advance_width = get_uint16_little(hmtx->advance_width);
	spacing.rsb = spacing.advance_width - spacing.lsb - spacing.width;

	return spacing;
}

TTF_CharDims ttf_get_char_dims_scaled(
	const uint8_t* font,
	char charcode,
	float scale
) {
	TTF_CharDims dims = ttf_get_char_dims(font, charcode);

	dims.x *= scale;
	dims.y *= scale;
	dims.max_x *= scale;
	dims.max_y *= scale;
	dims.lsb *= scale;
	dims.advance_width *= scale;

	// Recalculate the derived quantites again otherwise they may not match up
	// due to rounding errors
	dims.width = dims.max_x - dims.x;
	dims.height = dims.max_y - dims.y;
	dims.rsb = dims.advance_width - dims.lsb - dims.width;

	return dims;
}

float ttf_get_scale(const uint8_t* font, uint16_t font_size_pt, uint16_t screen_ppi) {
	TTF_head* head = (TTF_head*)ttf_get_table(font, TTF_TABLE_HEAD);
	const int points_per_inch = 72;
	uint16_t units_per_em_little = get_uint16_little(head->units_per_em);

	return (float)(font_size_pt * screen_ppi) / (points_per_inch * units_per_em_little);
}
