#ifndef __HAREWARE_H__
#define __HAREWARE_H__

#include "hal_lcd.h"

typedef struct
{
	hal_lcd_t hal_lcd;
}hardware_t;

extern hardware_t hardware;;

extern void hardware_init(void);

#endif

