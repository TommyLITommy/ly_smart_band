#ifndef __HAL_LCD_H__
#define __HAL_LCD_H__

#include "sdk_common.h"

//������ɫ
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
#define BROWN 			     0XBC40 //��ɫ
#define BRRED 			     0XFC07 //�غ�ɫ
#define GRAY  			     0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			     0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

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
