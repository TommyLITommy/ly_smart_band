#ifndef __HAL_LCD_H__
#define __HAL_LCD_H__

#include "sdk_common.h"

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

typedef struct
{
	void(*lcd_init)(void);
	void(*lcd_uninit)(void);
	void(*lcd_draw_pixel)(uint16_t x, uint16_t y, uint16_t color);
	void(*lcd_draw_picture)(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t *pic);
	void(*lcd_draw_line)(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
	void(*lcd_fill)(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
}hal_lcd_t;

extern void hal_lcd_init(hal_lcd_t *p_hal_lcd);

#endif
