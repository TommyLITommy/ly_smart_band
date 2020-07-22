#ifndef __DRAW_DIGIT_H__
#define __DRAW_DIGIT_H__

#include "sdk_common.h"

typedef enum
{
	DIGIT_TYPE_TIME_HOUR,
	DIGIT_TYPE_TIME_MINUTE,
}digit_type_t;

extern void draw_digit(uint16_t top_left_corner_x, uint16_t top_left_corner_y, uint8_t digit, uint8_t digit_type);
extern uint8_t get_digit_length(uint8_t digit_type);

#endif
