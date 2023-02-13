#ifndef __TTF_STRUCTS_H
#define __TTF_STRUCTS_H

#include <stdint.h>

// Table Tag hex values
#define TTF_TABLE_FFTM (0x4d544646)
#define TTF_TABLE_GDEF (0x46454447)
#define TTF_TABLE_OS2 (0x322f534f)
#define TTF_TABLE_CMAP (0x70616d63)
#define TTF_TABLE_CVT (0x20747663)
#define TTF_TABLE_FPGM (0x6d677066)
#define TTF_TABLE_GASP (0x70736167)
#define TTF_TABLE_GLYF (0x66796c67)
#define TTF_TABLE_HEAD (0x64616568)
#define TTF_TABLE_HHEA (0x61656868)
#define TTF_TABLE_HMTX (0x78746d68)
#define TTF_TABLE_LOCA (0x61636f6c)
#define TTF_TABLE_MAXP (0x7078616d)
#define TTF_TABLE_NAME (0x656d616e)
#define TTF_TABLE_POST (0x74736f70)
#define TTF_TABLE_PREP (0x70657270)

// glyf table flag values
#define TTF_GLYF_ON_CURVE_POINT (0x01)
#define TTF_GLYF_X_SHORT_VECTOR (0x02)
#define TTF_GLYF_Y_SHORT_VECTOR (0x04)
#define TTF_GLYF_REPEAT (0x08)
#define TTF_GLYF_X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR (0x10)
#define TTF_GLYF_Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR (0x20)
#define TTF_GLYF_OVERLAP_SIMPLE (0x40)

typedef uint32_t Offset32;
typedef uint16_t Offset16;
typedef uint32_t Tag;
typedef uint32_t Fixed;
typedef int16_t FWord;
typedef uint16_t UFWord;
typedef uint64_t LongDateTime;

typedef struct {
	Tag table_tag;
	uint32_t checksum;
	Offset32 offset;
	uint32_t length;
} TableRecord;

typedef struct {
	uint32_t sfnt_version;
	uint16_t num_tables;
	uint16_t search_range;
	uint16_t entry_selector;
	uint16_t range_shift;
	TableRecord table_records[]; // # of els: numTables
} TableDirectory;

typedef struct {
	Fixed version;
	Fixed font_revision;
	uint32_t check_sum_adjustment;
	uint32_t magic_number;
	uint16_t flags;
	uint16_t units_per_em;
	LongDateTime created;
	LongDateTime modified;
	FWord x_min;
	FWord y_min;
	FWord x_max;
	FWord y_max;
	uint16_t mac_style;
	uint16_t lowest_rec_ppem;
	int16_t font_direction_hint;
	int16_t index_to_loc_format; // 0 for short offsets (Offset16), 1 for long (Offset32)
	int16_t glyph_data_format;
} TTF_head;

typedef struct {
	Fixed version;
	uint16_t num_glyphs;
	uint16_t max_points;
	uint16_t max_contours;
	uint16_t max_components_points;
	uint16_t max_component_contours;
	uint16_t max_zones;
	uint16_t max_twilight_points;
	uint16_t max_storage;
	uint16_t max_function_defs;
	uint16_t max_instruction_defs;
	uint16_t max_stack_elements;
	uint16_t max_size_of_instructions;
	uint16_t max_component_elements;
	uint16_t max_component_depth;
} TTF_maxp;

typedef struct {
	uint16_t major_version;
	uint16_t minor_version;
	FWord ascender;
	FWord descender;
	FWord line_gap;
	UFWord advance_width_max;
	FWord min_left_side_bearing;
	FWord min_right_side_bearing;
	FWord x_max_extent;
	int16_t caret_slope_rise;
	int16_t caret_slope_run;
	int16_t caret_offset;
	int16_t __reserved_1;
	int16_t __reserved_2;
	int16_t __reserved_3;
	int16_t __reserved_4;
	int16_t metric_data_format;
	uint16_t number_of_h_metrics;
} TTF_hhea;

typedef struct {
	uint16_t advance_width;
	int16_t lsb;
} TTF_hmtxLongHorMetric;

typedef struct {
	TTF_hmtxLongHorMetric h_metrics; // Array with size number_of_h_metrics
	int16_t left_side_bearings[]; // Array with size num_glyphs - number_of_h_metrics
} TTF_hmtx;

typedef struct {
	Offset16 offsets; // Array of offsets with size num_glyphs
} TTF_locaShort;

typedef struct {
	Offset32 offsets; // Array of offsets with size num_glyphs
} TTF_locaLong;

typedef struct {
	int16_t number_of_contours;
	int16_t x_min;
	int16_t y_min;
	int16_t x_max;
	int16_t y_max;
} TTF_glyfHead;

// This struct is literally just for reference for the relative
// order of values. The bytes themselves are very misaligned from
// the struct.
typedef struct {
	uint16_t end_pts_of_contours; // Array of size number_of_contours
	uint16_t instruction_length;
	uint8_t instructions; // Array of size instruction_length
	uint8_t flags; // Array of size equal to the number of points between all contours
	uint8_t x_coordinates; // Array of variable size depending on point count and flags
	uint8_t y_coordinates; // Array of variable size depending on point count and flags
} TTF_glyfBody;

typedef struct {
	uint16_t platform_id;
	uint16_t encoding_id;
	Offset32 offset;
} TTF_cmapEncodingRecord;

typedef struct {
	uint16_t format;
	uint16_t length;
	uint16_t language;
	uint16_t seg_count_x2; // == seg_count * 2
	uint16_t search_range;
	uint16_t entry_selector;
	uint16_t range_shift;

	// Past this point, the values get quite misaligned from the struct,
	// so these members are pretty much just for reference
	uint16_t end_code; // Size of array is seg_count
	uint16_t reserved_pad;
	uint16_t start_code; // Size of array is seg_count
	int16_t id_delta; // Size of array is seg_count
	uint16_t id_range_offsets; // Size of array is seg_count
	uint16_t glyph_id_array; // Arbitrary size array
} TTF_cmapSubtableFormat4;

typedef struct {
	uint16_t version;
	uint16_t num_tables;
	TTF_cmapEncodingRecord encoding_records[];
} TTF_cmap;

typedef struct {
	int16_t x;
	int16_t y;
	int16_t max_x;
	int16_t max_y;
	int16_t width;
	int16_t height;
	int16_t lsb;
	int16_t rsb;
	int16_t advance_width;
} TTF_CharDims;

typedef struct TTF_Point_ {
	int16_t x;
	int16_t y;
	struct TTF_Point_* next;
	uint8_t on_curve;
	uint8_t flag;
	uint8_t is_contour_start;
	uint8_t is_contour_end;
	uint16_t contour_index;
	uint16_t contour;
} TTF_Point;

#endif