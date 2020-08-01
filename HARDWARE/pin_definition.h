#ifndef __PIN_DEFINITION_H__
#define __PIN_DEFINITION_H__

//Peripheral power relative
#define PERIPHERAL_VDD_EN_PIN_NUMBER					6
#define PERIPHERAL_VLED_EN_PIN_NUMBER					14
#define PERIPHERAL_9VDD_EN_PIN_NUMBER					15

//OLED relative
#define OLED_CS_PIN_NUMBER								24
#define OLED_MOSI_PIN_NUMBER							20
#define OLED_MISO_PIN_NUMBER				
#define OLED_SCLK_PIN_NUMBER							21
#define OLED_DC_PIN_NUMBER								22
#define OLED_RES_PIN_NUMBER								23

//G-Sensor relative
#if 1
#define G_SENSOR_INIT1_PIN_NUMBER						29
#define G_SENSOR_MOSI_PIN_NUMBER						26
#define G_SENSOR_MISO_PIN_NUMBER						27
#define G_SENSOR_CS_PIN_NUMBER							28
#define G_SENSOR_SCLK_PIN_NUMBER						25
#else
#define G_SENSOR_INIT1_PIN_NUMBER						16
#define G_SENSOR_MOSI_PIN_NUMBER						17
#define G_SENSOR_MISO_PIN_NUMBER						18
#define G_SENSOR_CS_PIN_NUMBER							19
#define G_SENSOR_SCLK_PIN_NUMBER						31
#endif

//GT24L24A2Y_relative
#define GT24L24A2Y_CS_PIN_NUMBER						30
#define GT24L24A2Y_MOSI_PIN_NUMBER						26
#define GT24L24A2Y_MISO_PIN_NUMBER						27
#define GT24L24A2Y_SCLK_PIN_NUMBER						25

//Touch key relative
#define TOUCH_KEY_PRESS_DETECT_PIN_NUMBER				7
#define TOUCH_KEY_POWER_SUPPLY_PIN_NUMBER				8

//Motor relative
#define MOTOR_CONTROL_PIN_NUMBER						2

//Charging relative
#define CHARGING_DETECT_PIN_NUMBER						4

//Usb insert detect
#define USB_INSERT_DETECT_PIN_NUMBER					5

//Unused pin
#define UNUSE_PIN_P_0_00_XL1                            0
#define UNUSE_PIN_P_0_01_XL2							1

#define UNUSED_PIN_P_0_09_NFC1							9
#define UNUSED_PIN_P_0_10_NFC2                          10

#define UNUSED_PIN_P_0_16                               16
#define UNUSED_PIN_P_0_17                               17
#define UNUSED_PIN_P_0_18                               18
#define UNUSED_PIN_P_0_19                               19
#define UNUSED_PIN_P_0_31                               31

// Low frequency clock source to be used by the SoftDevice
#if 0
#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_XTAL,            \
                                 .rc_ctiv       = 0,                                \
                                 .rc_temp_ctiv  = 0,                                \
                                 .xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM}
#else
#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_RC,            \
                                 .rc_ctiv       = 16,                                \
                                 .rc_temp_ctiv  = 2,    \
                                 .xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_250_PPM}                                 
#endif


#endif

