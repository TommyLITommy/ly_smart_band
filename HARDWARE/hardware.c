#include "hardware.h"

hardware_t hardware;

void hardware_init(void)
{
	hal_lcd_init(&hardware.hal_lcd);
}
