#include <math.h>
#include "sys_info.h"
#include "draw_common.h"
#include "ui_analog_clock.h"

const display_area_t uac_display_area[UIAC_DISPLAY_AREA_MAX] = 
{
	{7,7,226,226},//UIAC_DISPLAY_DIAL
	{96,45,47,17},//UIAC_DISPLAY_DATE
	//{},//UIAC_DISPLAY_HAND_HOUR
	//{},//UIAC_DISPLAY_HAND_MINUTE
};

static uint8_t hour = 0;
static uint8_t minute = 0;

static void draw_analog_clock_minute_hand(uint16_t origin_x, uint16_t origin_y, uint8_t minute, uint16_t color)
{
	int32_t x, y;
	uint8_t a, b;
	x = MINUTE_HAND_LENGTH * cos(PI / 2 - DEG_TO_RAD(6 * minute));
	y = MINUTE_HAND_LENGTH * sin(PI / 2 - DEG_TO_RAD(6 * minute));
	for(a = 0; a < 5; a++)
	{
		for(b = 0; b < 5; b++)
		{
			sys_info.hardware.drv_lcd.drv_lcd_draw_line(origin_x + a, origin_y + b, origin_x + a + x, origin_y + b - y, color);
		}
	}
}

//what about picture rotate here?
static void draw_analog_clock_hour(uint16_t origin_x, uint16_t origin_y, uint8_t hour, uint8_t minute, uint16_t color)
{
	int32_t x, y;
	uint8_t a, b;
	x = HOUR_HAND_LENGTH * cos(PI / 2 - DEG_TO_RAD(30 * hour + ((float)(minute) / (float)60) * (float)30));
	y = HOUR_HAND_LENGTH * sin(PI / 2 - DEG_TO_RAD(30 * hour + ((float)(minute) / (float)60) * (float)30));
	for(a = 0; a < 4; a++)
	{
		for(b = 0; b < 4; b++)
		{
			sys_info.hardware.drv_lcd.drv_lcd_draw_line(origin_x + a , origin_y + b, origin_x + a + x, origin_y + b - y, color);
		}
	}
}


bool change = 0;

void draw_clock(void)
{
	//Why put those code here will casue hardfault???
	/*
	static uint8_t minute = 0;
	if(change)
	{	
		change = 0;
		draw_analog_clock_minute_hand(ANALOG_CLOCK_ORIGINAL_X, ANALOG_CLOCK_ORIGINAL_Y, minute, BLACK);
		if(++minute == 60)
		{
			minute = 0;
		}
		draw_analog_clock_minute_hand(ANALOG_CLOCK_ORIGINAL_X, ANALOG_CLOCK_ORIGINAL_Y, minute, RED);
	}
	*/
	change = 1;	
}

void ui_analog_clock_enter(void)
{
	
}

void ui_analog_clock_exit(void)
{
	draw_analog_clock_minute_hand(ANALOG_CLOCK_ORIGINAL_X, ANALOG_CLOCK_ORIGINAL_Y, minute, BLACK);
}

void ui_analog_clock_show(void)
{
	if(change)
	{	
		change = 0;
		draw_analog_clock_minute_hand(ANALOG_CLOCK_ORIGINAL_X, ANALOG_CLOCK_ORIGINAL_Y, minute, BLACK);
		if(++minute == 60)
		{
			minute = 0;
		}
		draw_analog_clock_minute_hand(ANALOG_CLOCK_ORIGINAL_X, ANALOG_CLOCK_ORIGINAL_Y, minute, RED);
	}
}

void ui_analog_clock_init(void)
{
	
}
