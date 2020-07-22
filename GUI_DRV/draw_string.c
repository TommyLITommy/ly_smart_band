#include "hardware.h"
#include "hal_lcd.h"
#include "draw_character.h"
#include "draw_string.h"

void draw_string(uint16_t top_left_corner_x, uint16_t top_left_corner_y, uint8_t *string, uint8_t character_font_type, uint8_t character_interval, uint16_t color)
{
	uint8_t index;
	uint8_t character;
	uint8_t character_width;

	switch(character_font_type)
	{
		case CHARACTER_FONT_TYPE_ASCII_5X7:
		case CHARACTER_FONT_TYPE_ASCII_7X8:
			character_width = 8;
			break;
		case CHARACTER_FONT_TYPE_ASCII_6X12:
			character_width = 6;
			break;
		case CHARACTER_FONT_TYPE_ASCII_8X16:
			character_width = 8;
			break;
		case CHARACTER_FONT_TYPE_ASCII_12X24:
			character_width = 12;
			break;
		case CHARACTER_FONT_TYPE_ASCII_16X32:
			character_width = 16;
	}
	
	#if 0
    uint8_t total_length;
    total_length = strlen((char *)string) * character_width;
	if(align_center)
	{
		top_left_corner_x = center_position - total_length / 2;
	}
	#endif
	
	index = 0;
	character = string[index++];
	while(character != '\0')
	{
		draw_character(top_left_corner_x, top_left_corner_y, character, character_font_type, color);
		character = string[index++];
		top_left_corner_x += character_interval + character_width;
	}
}
