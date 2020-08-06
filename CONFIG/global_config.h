#ifndef __GLOBAL_CONFIG_H__
#define __GLOBAL_CONFIG_H__

//#define ENABLE_PAIRING 

#define LY_LOG_MODULE_ENABLED(module) \
    ((defined(module ## _ENABLED) && (module ## _ENABLED)) ? 1 : 0)


#define ENABLE_ST7789_GPIO_SIMULATE_SPI 1
//#define ENABLE_ST7789_HARDWARE_SPI		1

#endif
