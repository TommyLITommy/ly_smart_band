#include "hardware.h"

void draw_monochrome_font_array(uint16_t top_left_corner_x, uint16_t top_left_corner_y, uint16_t font_array_row, uint16_t font_array_column, uint16_t font_actual_row, uint16_t font_actual_column, uint8_t *p_buffer, uint16_t color)
{
	uint16_t i, j, m;
	uint8_t temp;
	
	for(i = 0; i < font_array_row; i++)
	{
		for(j = 0; j < font_array_column; j++)
		{
			temp = p_buffer[font_array_column * i + j];
			
			for(m = 0; m < 8; m++)
			{
				if(temp & 0x01)
				{
					hardware.hal_lcd.lcd_draw_pixel(top_left_corner_x + j,  top_left_corner_y + 8 * i + m, color);
				}
                
                temp = temp >> 1;
			}
		}
	}
}
