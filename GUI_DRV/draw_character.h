#ifndef __DRAW_CHARACTER_H__
#define __DRAW_CHARACTER_H__

typedef enum
{
	CHARACTER_FONT_TYPE_ASCII_5X7 = 0,
	CHARACTER_FONT_TYPE_ASCII_7X8,
	CHARACTER_FONT_TYPE_ASCII_6X12,
	CHARACTER_FONT_TYPE_ASCII_8X16,
	CHARACTER_FONT_TYPE_ASCII_12X24,
	CHARACTER_FONT_TYPE_ASCII_16X32,
}character_font_type_t;

extern void draw_character(uint16_t top_left_corner_x, uint16_t top_left_corner_y, uint8_t character_ascii, uint8_t character_font_type, uint16_t color);

#endif

