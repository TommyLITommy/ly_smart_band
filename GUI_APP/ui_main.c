#include "draw_common.h"
#include "ui_main.h"

uint8_t integer = 0;

const display_area_t uim_display_area[UIM_DISPLAY_AREA_MAX] =
{
	{20,18,16,20},		//UIM_DISPLAY_AREA_BLUETOOTH
	{94,18,53,20},		//UIM_DISPLAY_AREA_DATE
	{190,18,30,20},		//UIM_DISPLAY_AREA_BATTERY
	{27,60,120,91},		//UIM_DISPLAY_AREA_TIME_HOUR
	{157,110,55,42},	//UIM_DISPLAY_AREA_TIME_MINUTE
	{178,77,35,17},		//UIM_DISPLAY_AREA_WEEK
	{32,187,24,20},		//UIM_DISPLAY_AREA_HEART_RATE
	{135,183,21,24},	//UIM_DISPLAY_AREA_BLOOD_PRESSURE
	{18,174,100,46},	//UIM_DISPLAY_AREA_OVAL_FRAME_01
	{123,174,100,46},   //UIM_DISPLAY_AREA_OVAL_FRAME_02
	{65,189,27,16},		//UIM_DISPLAY_AREA_HR_DATA
	{161,188,53,16}		//UIM_DISPLAY_AREA_BP_DATA				
};

void ui_main_enter(void)
{
	draw_icon(&uim_display_area[UIM_DISPLAY_AREA_OVAL_FRAME_01], ICON_ID_OVAL_FRAME_01);
	draw_icon(&uim_display_area[UIM_DISPLAY_AREA_OVAL_FRAME_02], ICON_ID_OVAL_FRAME_02);
	draw_icon(&uim_display_area[UIM_DISPLAY_AREA_HEART_RATE], ICON_ID_HEART_RATE);
	draw_icon(&uim_display_area[UIM_DISPLAY_AREA_BLOOD_PRESSURE], ICON_ID_BLOOD_PRESSURE);
}

void ui_main_exit(void)
{
	for(uint8_t i = (uint8_t)UIM_DISPLAY_AREA_BLUETOOTH; i < (uint8_t)UIM_DISPLAY_AREA_MAX; i++)
	{
		draw_rectangle(&uim_display_area[i], 0x00);
	}
}


void ui_main_show(void)
{	
	ui_main_enter();
	draw_icon(&uim_display_area[UIM_DISPLAY_AREA_BLUETOOTH], ICON_ID_BLUETOOTH);
	switch(integer % 5)
	{
		case 0:
			draw_icon(&uim_display_area[UIM_DISPLAY_AREA_BATTERY], ICON_ID_BATTERY_01);
			break;
		case 1:
			draw_icon(&uim_display_area[UIM_DISPLAY_AREA_BATTERY], ICON_ID_BATTERY_02);
			break;
		case 2:
			draw_icon(&uim_display_area[UIM_DISPLAY_AREA_BATTERY], ICON_ID_BATTERY_03);
			break;
		case 3:
			draw_icon(&uim_display_area[UIM_DISPLAY_AREA_BATTERY], ICON_ID_BATTERY_04);
			break;
		case 4:
			draw_icon(&uim_display_area[UIM_DISPLAY_AREA_BATTERY], ICON_ID_BATTERY_00);
			break;
		default:
			break;
	}
	draw_integer(27,60,integer,DIGIT_TYPE_TIME_HOUR,0);
    draw_integer(157,110,integer,DIGIT_TYPE_TIME_MINUTE,0);
    draw_chinese(178, 77, 0, 0, 0x001F);
	if(++integer >= 100)
	{
		integer = 0;
	}
}

void ui_main_init(void)
{

}
