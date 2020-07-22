#include "draw_digit.h"
#include "draw_integer.h"

#define TEN_MILLION  		10000000
#define INTEGER_MAX_VALUE	(TEN_MILLION - 1)
#define MAX_DIGIT			8

void draw_integer(uint16_t top_left_corner_x, uint16_t top_left_corner_y, uint32_t integer, uint8_t digit_type, uint8_t interval)
{
	int8_t i, j, digit_count = 0;
	uint8_t total_length;
	uint8_t value[MAX_DIGIT] = {0};
	
	if(integer > INTEGER_MAX_VALUE)
	{
		return;
	}
	
	for(i = 0; i < MAX_DIGIT; i++)
	{
		value[i] = integer % 10;
		digit_count++;
		
		integer = integer / 10;
		if(!integer)
		{
			break;
		}
	}
	
	switch(digit_type)
	{
		case DIGIT_TYPE_TIME_HOUR:
			break;
		case DIGIT_TYPE_TIME_MINUTE:
			break;
		default:
			break;
	}
	
	total_length = 0;
	
	for(i = 0; i < digit_count; i++)
	{
		j = digit_count - 1 - i;
		
		draw_digit(top_left_corner_x + total_length, top_left_corner_y, value[j], digit_type);
		total_length = total_length + get_digit_length(digit_type) + interval;
	}
}
