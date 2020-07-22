#ifndef __ST7789_H__
#define __ST7789_H__

extern void st7789_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
extern void st7789_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
extern void st7789_draw_picture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t *pic);
extern void st7789_fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
extern void st7789_init(void);

#endif
