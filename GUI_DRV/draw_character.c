#include "hardware.h"
#include "GT24L24A2Y.h"
#include "draw_monochrome_font_array.h"
#include "draw_character.h"

#define CHARACTER_FONT_BUFFER_SIZE 128

void draw_character(uint16_t top_left_corner_x, uint16_t top_left_corner_y, uint8_t character_ascii, uint8_t character_font_type, uint16_t color)
{
	uint8_t match = 0;
	uint8_t character_font_buffer[CHARACTER_FONT_BUFFER_SIZE];
	uint8_t font_array_row;
	uint8_t font_array_column;
	uint8_t font_actual_row, font_actual_column;
	uint8_t font_array_start_index;
	
	switch(character_font_type)
	{
		case CHARACTER_FONT_TYPE_ASCII_5X7:
			ASCII_GetData(character_ascii, ASCII_5X7, character_font_buffer);
			font_array_row 	  	= 1;
			font_array_column 	= 8;
			font_actual_row   	= 8;
			font_actual_column 	= 8;
			font_array_start_index 	= 0;
			match = 1;
			break;
		case CHARACTER_FONT_TYPE_ASCII_7X8:
			ASCII_GetData(character_ascii, ASCII_7X8, character_font_buffer);
			font_array_row 	  	= 1;
			font_array_column 	= 8;
			font_actual_row   	= 8;
			font_actual_column 	= 8;
			font_array_start_index 	= 0;
			match = 1;
			break;
		case CHARACTER_FONT_TYPE_ASCII_6X12:
			ASCII_GetData(character_ascii, ASCII_6X12, character_font_buffer);
			font_array_row 	  	= 2;
			font_array_column 	= 6;
			font_actual_row   	= 12;
			font_actual_column 	= 6;
			font_array_start_index 	= 0;
			match = 1;
			break;
		case CHARACTER_FONT_TYPE_ASCII_8X16:
			ASCII_GetData(character_ascii, ASCII_8X16, character_font_buffer);
			font_array_row 	  	= 2;
			font_array_column 	= 8;
			font_actual_row   	= 16;
			font_actual_column 	= 8;
			font_array_start_index 	= 0;
			match = 1;
			break;
		case CHARACTER_FONT_TYPE_ASCII_12X24:
			ASCII_GetData(character_ascii, ASCII_12X24, character_font_buffer);
			font_array_row 	  	= 3;
			font_array_column 	= 12;
			font_actual_row   	= 24;
			font_actual_column 	= 12;
			font_array_start_index 	= 0;
			match = 1;
			break;
		case CHARACTER_FONT_TYPE_ASCII_16X32:
			ASCII_GetData(character_ascii, ASCII_16X32, character_font_buffer);
			font_array_row 	  	= 4;
			font_array_column 	= 16;
			font_actual_row   	= 32;
			font_actual_column 	= 16;
			font_array_start_index 	= 0;
			match = 1;
			break;
		default:
			break;
	}
	
	if(match)
	{
		draw_monochrome_font_array(top_left_corner_x, top_left_corner_y, font_array_row, font_array_column, font_actual_row, font_actual_column, character_font_buffer, color);
	}
}

