#include "sys_info.h"
#include "draw_digit.h"

extern const unsigned char *icon_time_hour[10];
extern const unsigned char *icon_time_minute[10];
void draw_digit(uint16_t top_left_corner_x, uint16_t top_left_corner_y, uint8_t digit, uint8_t digit_type)
{
	uint16_t length, width;
	const uint8_t *p_buffer;
	bool match = false;
	switch(digit_type)
	{
		case DIGIT_TYPE_TIME_HOUR:
			length = 62;
			width = 91;
			p_buffer = icon_time_hour[digit];
			match = true;
			break;
		case DIGIT_TYPE_TIME_MINUTE:
			length = 29;
			width = 42;
			p_buffer = icon_time_minute[digit];
			match = true;
			break;
		default:
			break;
	}
	
	if(match)
	{
		sys_info.hardware.drv_lcd.drv_lcd_draw_picture(top_left_corner_x, top_left_corner_y, length, width, p_buffer);
	}	
}

uint8_t get_digit_length(uint8_t digit_type)
{
	uint8_t digit_length = 0;
	switch(digit_type)
	{
		case DIGIT_TYPE_TIME_HOUR:
			digit_length = 62;
			break;
		case DIGIT_TYPE_TIME_MINUTE:
			digit_length = 29;
			break;
		default:
			break;
	}
    return digit_length;
}


