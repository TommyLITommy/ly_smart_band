#include "sys_info.h"
#include "draw_rectangle.h"


void draw_rectangle(const display_area_t *p_display_area, uint16_t color)
{
	sys_info.hardware.drv_lcd.drv_lcd_fill(p_display_area->x_start, p_display_area->y_start, p_display_area->x_start + p_display_area->length, p_display_area->y_start + p_display_area->width, color);
}
