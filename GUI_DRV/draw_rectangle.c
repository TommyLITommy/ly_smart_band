#include "hardware.h"
#include "hal_lcd.h"
#include "draw_rectangle.h"


void draw_rectangle(const display_area_t *p_display_area, uint16_t color)
{
	hardware.hal_lcd.lcd_fill(p_display_area->x_start, p_display_area->y_start, p_display_area->x_start + p_display_area->length, p_display_area->y_start + p_display_area->width, color);
}
