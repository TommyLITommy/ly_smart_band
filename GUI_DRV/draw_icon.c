#include "hardware.h"
#include "hal_lcd.h"
#include "draw_icon.h"
#include "st7789.h"
#include "drv_flash.h"
#include "sys_info.h"

//#define ENABLE_UI_MAIN
//#define EANBLE_UI_ANALOG_CLOCK
//#define ENABLE_UI_CHARGING
//#define ENABLE_UI_NOTIFICATION
//#define ENABLE_UI_HEART_RATE_MEASURE
//#define EANBLE_UI_BLOOD_PRESSURE_MEASURE
//#define ENABLE_UI_TIRE_SETTING
//#define ENABLE_UI_TS_TYPE_SELECT
//#define ENABLE_UI_TS_TIRE_SELECT_MOTOR
//#define ENABLE_UI_TS_TIRE_SELECT_CAR
//#define ENABLE_UI_TS_TIRE_SELECT_SUV
//#define ENABLE_UI_TP_MOTOR
//#define ENABLE_UI_TP_CAR
//#define ENABLE_UI_TP_SUV
//#define ENABLE_UI_TS_TIRE_BINDING

#ifdef ENABLE_UI_MAIN
extern const unsigned char icon_bluetooth[];//Why does those array have been optimised out?
extern const unsigned char icon_battery_00[];
extern const unsigned char icon_battery_01[];
extern const unsigned char icon_battery_02[];
extern const unsigned char icon_battery_03[];
extern const unsigned char icon_battery_04[];
extern const unsigned char icon_heart_rate[];
extern const unsigned char icon_blood_pressure[];
extern const unsigned char icon_oval_frame[];
#else
#define icon_bluetooth  		NULL
#define icon_battery_00			NULL
#define icon_battery_01 		NULL
#define icon_battery_02 		NULL
#define icon_battery_03 		NULL
#define icon_battery_04			NULL
#define icon_heart_rate			NULL
#define icon_blood_pressure		NULL
#define icon_oval_frame			NULL
#endif

#ifdef EANBLE_UI_ANALOG_CLOCK
#else
#endif

#ifdef ENABLE_UI_HEART_RATE_MEASURE
extern const unsigned char icon_heart_rate_01[];
#else
#define icon_heart_rate_01    	NULL
#endif

#ifdef EANBLE_UI_BLOOD_PRESSURE_MEASURE
extern const unsigned char icon_blood_pressure_01[];
#else
#define icon_blood_pressure_01  NULL
#endif

#ifdef ENABLE_UI_NOTIFICATION
//notification
extern const unsigned char icon_qq[];
extern const unsigned char icon_wechat[];
extern const unsigned char icon_text[];
extern const unsigned char icon_incoming_call[];
extern const unsigned char icon_oval_frame_03[];
#else
#define icon_qq 				NULL
#define icon_wechat				NULL
#define icon_text				NULL
#define icon_incoming_call		NULL
#define icon_oval_frame_03		NULL
#endif

#ifdef ENABLE_UI_CHARGING
//charging
extern const unsigned char icon_charging_00[];
extern const unsigned char icon_charging_01[];
extern const unsigned char icon_charging_02[];
extern const unsigned char icon_charging_03[];
extern const unsigned char icon_charging_04[];
#else
#define icon_charging_00		NULL
#define icon_charging_01		NULL
#define icon_charging_02		NULL
#define icon_charging_03		NULL
#define icon_charging_04		NULL
#endif


#ifdef ENABLE_UI_TIRE_SETTING
extern const unsigned char icon_tire_setting[];
extern const unsigned char icon_tire_setting_name[];
#else
#define icon_tire_setting		NULL
#define icon_tire_setting_name  NULL
#endif

#ifdef ENABLE_UI_TS_TYPE_SELECT
extern const unsigned char icon_ts_type_select[];
extern const unsigned char icon_ts_type_deselect[];
#else
#define icon_ts_type_select		NULL
#define icon_ts_type_deselect   NULL
#endif

#if 1
#define icon_tire_select	NULL
#define icon_tire_deselect 	NULL
#define icon_back_select	NULL
#define icon_back_deselect	NULL
#define icon_ok_select		NULL
#define icon_ok_deselect	NULL
#else
/*tire setting*/
extern const unsigned char icon_tire_select[];
extern const unsigned char icon_tire_deselect[];
extern const unsigned char icon_back_select[];
extern const unsigned char icon_back_deselect[];
extern const unsigned char icon_ok_select[];
extern const unsigned char icon_ok_deselect[];
#endif

#ifdef ENABLE_UI_TS_TIRE_SELECT_MOTOR
extern const unsigned char icon_motor_body[];
#else
#define icon_motor_body      	NULL
#endif

#ifdef ENABLE_UI_TS_TIRE_SELECT_CAR
extern const unsigned char icon_car_body[];
#else
//#define icon_car_body			NULL
#endif

#ifdef ENABLE_UI_TS_TIRE_SELECT_SUV
extern const unsigned char icon_car_body[];
#else
#define icon_car_body			NULL
#endif

#if 1
#define icon_car_suv_h_tire_blue	NULL
#define icon_car_suv_h_tire_gray	NULL
#define icon_car_suv_h_tire_red		NULL
#define icon_car_suv_v_tire_blue	NULL
#define icon_car_suv_v_tire_gray	NULL
#define icon_car_suv_v_tire_red		NULL
#else
/*tire color*/
extern const unsigned char icon_car_suv_h_tire_blue[];
extern const unsigned char icon_car_suv_h_tire_gray[];
extern const unsigned char icon_car_suv_h_tire_red[];
extern const unsigned char icon_car_suv_v_tire_blue[];
extern const unsigned char icon_car_suv_v_tire_gray[];
extern const unsigned char icon_car_suv_v_tire_red[];
#endif

#ifdef ENABLE_UI_TS_TIRE_BINDING
extern const unsigned char icon_tire_binding_name[];
#else
#define icon_tire_binding_name NULL
#endif

//static hal_lcd_t *hal_lcd;
extern hardware_t hardware;

const uint8_t *icon_array[ICON_ID_MAX] =
{
	//ui_main
	icon_bluetooth,//ICON_ID_BLUETOOTH
	icon_battery_00,//ICON_ID_BATTERY_00,
	icon_battery_01,//ICON_ID_BATTERY_01,
	icon_battery_02,//ICON_ID_BATTERY_02,
	icon_battery_03,//ICON_ID_BATTERY_03,
	icon_battery_04,//ICON_ID_BATTERY_04,
	icon_heart_rate,//ICON_ID_HEART_RATE,
	icon_blood_pressure,//ICON_ID_BLOOD_PRESSURE,
	icon_oval_frame,//ICON_ID_OVAL_FRAME_01,
	icon_oval_frame,//ICON_ID_OVAL_FRAME_02,
	//ui_analog_clock
	NULL,//ICON_ID_ANALOG_CLOCK_DIAL,
	NULL,//ICON_ID_ANALOG_CLOCK_HAND_HOUR,
	NULL,//ICON_ID_ANALOG_CLOCK_HAND_MINUTE,
	//ui_heart_rate_measure
	icon_heart_rate_01,//NULL,//ICON_ID_HEART_RATE_ICON,
	NULL,//ICON_ID_HERAT_RATE_UNIT,
	//ui_blood_pressure_measure
	icon_blood_pressure_01,//NULL,//ICON_ID_BLOOD_PRESSURE_ICON,
	NULL,//ICON_ID_BLOOD_PRESSURE_UNIT,
	//ui_notification
	icon_qq,//NULL,//ICON_ID_QQ,
	icon_wechat,//NULL,//ICON_ID_WECHAT,
	icon_text,//NULL,//ICON_ID_TEXT,
	icon_incoming_call,//NULL,//ICON_ID_INCOMING_CALL,
	icon_oval_frame_03,//NULL,//ICON_ID_OVAL_FRAME_03,
	NULL,//ICON_ID_CIRCLE_01_BLUE,
	NULL,//ICON_ID_CIRCLE_01_GRAY,
	//ui_charging
	icon_charging_00,//ICON_ID_CHARGING_00
	icon_charging_01,//ICON_ID_CHARGING_01,
	icon_charging_02,//ICON_ID_CHARGING_02,
	icon_charging_03,//ICON_ID_CHARGING_03,
	icon_charging_04,//ICON_ID_CHARGING_04,
	//ui_tire_setting
	icon_tire_setting,//NULL,//ICON_ID_TIRE_SETTING_ICON,
	icon_tire_setting_name,//NULL,//ICON_ID_TIRE_SETTING_NAME,
	//ui_ts_type_select
	icon_ts_type_deselect,//NULL,//ICON_ID_CIRCLE_02_BLUE,
	icon_ts_type_select,//NULL,//ICON_ID_CIRCLE_02_WHITE,
	/*tire setting*/
	icon_tire_select,//ICON_ID_TS_CIRCLE_BLUE,
	icon_tire_deselect,//ICON_ID_TS_CIRCLE_DARK_GRAY,
	icon_back_select,//ICON_ID_TS_BACK_SELECT,
	icon_back_deselect,//ICON_ID_TS_BACK_DESELECT,
	icon_ok_select,//ICON_ID_TS_OK_SELECT,
	icon_ok_deselect,//ICON_ID_TS_OK_DESELECT,
	icon_tire_binding_name,//ICON_ID_TS_TIRE_BINDING_NAME,
	//ui_tp_motor
	icon_motor_body,//ICON_ID_TP_MOTOR_BODY,
	NULL,//ICON_ID_TP_MOTOR_TIRE_RED,
	NULL,//ICON_ID_TP_MOTOR_TIRE_BLUE,
	NULL,//ICON_ID_TP_MOTOR_TIRE_GRAY,
	//car suv
	icon_car_body,//ICON_ID_TP_CAR_BODY,
	icon_car_body,//ICON_ID_TP_SUV_BODY,
	icon_car_suv_h_tire_red,//ICON_ID_TP_CAR_SUV_H_TIRE_RED,
	icon_car_suv_h_tire_blue,//ICON_ID_TP_CAR_SUV_H_TIRE_BLUE,
	icon_car_suv_h_tire_gray,//ICON_ID_TP_CAR_SUV_H_TIRE_GRAY,
	icon_car_suv_v_tire_red,//ICON_ID_TP_CAR_SUV_V_TIRE_RED,
	icon_car_suv_v_tire_blue,//ICON_ID_TP_CAR_SUV_V_TIRE_BLUE,
	icon_car_suv_v_tire_gray,//ICON_ID_TP_CAR_SUV_V_TIRE_GRAY,
};


#if 0
const icon_info_t icon_info[ICON_ID_MAX] =
{
	{},//ICON_ID_BLUETOOTH,
	{},//ICON_ID_BATTERY_00,
	{},//ICON_ID_BATTERY_01,
	{},//ICON_ID_BATTERY_02,
	{},//ICON_ID_BATTERY_03,
	{},//ICON_ID_BATTERY_04,
	{},//ICON_ID_HEART_RATE,
	{},//ICON_ID_BLOOD_PRESSURE,
	{},//ICON_ID_OVAL_FRAME_01,
	{},//ICON_ID_OVAL_FRAME_02,
	//ui_analog_clock
	{},//ICON_ID_ANALOG_CLOCK_DIAL,
	{},//ICON_ID_ANALOG_CLOCK_HAND_HOUR,
	{},//ICON_ID_ANALOG_CLOCK_HAND_MINUTE,
	//ui_heart_rate_measure
	{},//ICON_ID_HEART_RATE_ICON,
	{},//ICON_ID_HERAT_RATE_UNIT,
	//ui_blood_pressure_measure
	{},//ICON_ID_BLOOD_PRESSURE_ICON,
	{},//ICON_ID_BLOOD_PRESSURE_UNIT,
	//ui_notification
	{},//ICON_ID_QQ,
	{},//ICON_ID_WECHAT,
	{},//ICON_ID_TEXT,
	{},//ICON_ID_INCOMING_CALL,
	{},//ICON_ID_OVAL_FRAME_03,
	{},//ICON_ID_CIRCLE_01_BLUE,
	{},//ICON_ID_CIRCLE_01_GRAY,
	//ui_charging
	{},//ICON_ID_CHARGING_00,
	{},//ICON_ID_CHARGING_01,
	{},//ICON_ID_CHARGING_02,
	{},//ICON_ID_CHARGING_03,
	{},//ICON_ID_CHARGING_04,
	//ui_tire_setting
	{},//ICON_ID_TIRE_SETTING_ICON,
	{},//ICON_ID_TIRE_SETTING_NAME,
	//ui_ts_type_select
	{},//ICON_ID_CIRCLE_02_BLUE,
	{},//ICON_ID_CIRCLE_02_WHITE,
	/*tire select*/
	{},//ICON_ID_TS_CIRCLE_BLUE,
	{},//ICON_ID_TS_CIRCLE_DARK_GRAY,
	{},//ICON_ID_TS_BACK_SELECT,
	{},//ICON_ID_TS_BACK_DESELECT,
	{},//ICON_ID_TS_OK_SELECT,
	{},//ICON_ID_TS_OK_DESELECT,
	{},//ICON_ID_TS_TIRE_BINDING_NAME,
	//ui_tp_motor
	{},//ICON_ID_TP_MOTOR_BODY,
	{},//ICON_ID_TP_MOTOR_TIRE_RED,
	{},//ICON_ID_TP_MOTOR_TIRE_BLUE,
	{},//ICON_ID_TP_MOTOR_TIRE_GRAY,
	//ui_tp_car ui_tp_suv
	{},//ICON_ID_TP_CAR_BODY,
	{},//ICON_ID_TP_SUV_BODY,
    {},//ICON_ID_TP_CAR_SUV_H_TIRE_RED,
    {},//ICON_ID_TP_CAR_SUV_H_TIRE_BLUE,
    {},//ICON_ID_TP_CAR_SUV_H_TIRE_GRAY,
    {},//ICON_ID_TP_CAR_SUV_V_TIRE_RED,
    {},//ICON_ID_TP_CAR_SUV_V_TIRE_BLUE,
    {},//ICON_ID_TP_CAR_SUV_V_TIRE_GRAY,
}
#endif

const icon_font_flash_info_t icon_font_flash_info[ICON_ID_MAX] = {
    { 0 , 640 },
    { 640 , 1200 },
    { 1840 , 1200 },
    { 3040 , 1200 },
    { 4240 , 1200 },
    { 5440 , 1200 },
    { 6640 , 960 },
    { 7600 , 1008 },
    { 8608 , 9200 },
    { 17808 , 9200 },
    { 4294967295 , 0 },
    { 4294967295 , 0 },
    { 4294967295 , 0 },
    { 27008 , 35912 },
    { 4294967295 , 0 },
    { 62920 , 35912 },
    { 4294967295 , 0 },
    { 98832 , 3200 },
    { 102032 , 3200 },
    { 105232 , 3200 },
    { 108432 , 7200 },
    { 115632 , 22000 },
    { 4294967295 , 0 },
    { 4294967295 , 0 },
    { 137632 , 37400 },
    { 175032 , 37400 },
    { 212432 , 37400 },
    { 249832 , 37400 },
    { 287232 , 37400 },
    { 324632 , 49928 },
    { 374560 , 3160 },
    { 377720 , 8192 },
    { 385912 , 8192 },
    { 394104 , 5000 },
    { 399104 , 5000 },
    { 404104 , 2592 },
    { 406696 , 2592 },
    { 409288 , 2592 },
    { 411880 , 2592 },
    { 414472 , 2556 },
    { 417028 , 40404 },
    { 4294967295 , 0 },
    { 4294967295 , 0 },
    { 4294967295 , 0 },
    { 457432 , 34560 },
    { 491992 , 34560 },
    { 526552 , 480 },
    { 527032 , 480 },
    { 527512 , 480 },
    { 527992 , 594 },
    { 528586 , 594 },
    { 529180 , 594 },
};


/*This is a asynchronous call for uart or ble*/

//There need start a timer? or using freertos's task scheduler！！！
void draw_icon(const display_area_t *p_display_area, uint8_t icon_id)
{
	uint16_t y = 0;
    //st7789_fill(0, 0, 100, 100, BRED);
    /*
    st7789_draw_picture(20,
                        18,
                        16,
                        20,
                        icon_bluetooth);
    */
    //read data from flash or pc or mobile phone!!!
    //DMA???

	//read one line each time!!!

	#if 0
	uint8_t line_buffer[240 * 2];
	for(uint16_t i = 0; i < p_display_area->width; i++)
	{
		//read one line from flash or pc or mobile phone
		drv_flash_read(FLASH_FIRST_SECTOR_START_ADDRESS + icon_font_flash_info[icon_id].offset, line_buffer, p_display_area->length);
        #if 0
		hardware.hal_lcd.lcd_draw_picture(p_display_area->x_start,
						  p_display_area->y_start + y, 
						  p_display_area->length, 
						  1,//p_display_area->width, 
						  line_buffer);
        #endif
		y++;
	}
	#endif

	#if 1
	if(icon_array[icon_id] != NULL)
	{
		#if 0
		hardware.hal_lcd.lcd_draw_picture(p_display_area->x_start,
								  p_display_area->y_start, 
								  p_display_area->length, 
								  p_display_area->width, 
								  icon_array[icon_id]);
		#else
		sys_info.hardware.drv_lcd.drv_lcd_draw_picture(p_display_area->x_start,
								  p_display_area->y_start, 
								  p_display_area->length, 
								  p_display_area->width, 
								  icon_array[icon_id]);
		#endif
	}
	#endif
};
