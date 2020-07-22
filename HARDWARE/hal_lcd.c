#include "sdk_common.h"
#include "st7789.h"
#include "hal_lcd.h"

void hal_lcd_init(hal_lcd_t *p_hal_lcd)
{
	p_hal_lcd->lcd_init = st7789_init;
	p_hal_lcd->lcd_uninit = NULL;
	p_hal_lcd->lcd_draw_pixel = st7789_draw_pixel;
	p_hal_lcd->lcd_draw_line = st7789_draw_line;
	p_hal_lcd->lcd_draw_picture = st7789_draw_picture;
	p_hal_lcd->lcd_fill = st7789_fill;
	p_hal_lcd->lcd_init();
    p_hal_lcd->lcd_fill(0, 0, 240, 240, BLACK);
}
