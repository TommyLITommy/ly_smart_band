#include "draw_common.h"
#include "ui_ts_tire_select_suv.h"

#define delta_y 12

const display_area_t uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_MAX] =
{
	{72,20-delta_y ,96,180},//UITSTSSUV_DISPLAY_AREA_SUV_BODY = 0,
	{80,51-delta_y,11,27},//UITSTSSUV_DISPLAY_AREA_TIRE_01,
	{15,25-delta_y,50,50},//UITSTSSUV_DISPLAY_AREA_TIRE_01_CIRCLE,
	{149,51-delta_y,11,27},//UITSTSSUV_DISPLAY_AREA_TIRE_02,
	{175,25-delta_y,50,50},//UITSTSSUV_DISPLAY_AREA_TIRE_02_CIRCLE,
	{80,153-delta_y,11,27},//UITSTSSUV_DISPLAY_AREA_TIRE_03,
	{15,130-delta_y,50,50},//UITSTSSUV_DISPLAY_AREA_TIRE_03_CIRCLE,
	{148,153-delta_y,11,27},//UITSTSSUV_DISPLAY_AREA_TIRE_04,
	{175,130-delta_y,50,50},//UITSTSSUV_DISPLAY_AREA_TIRE_04_CIRCLE,
	{105,167,30,8},//UITSTSSUV_DISPLAY_AREA_TIRE_05,
	{95,178+12,50,50},//UITSTSSUV_DISPLAY_AREA_TIRE_05_CIRCLE,
	{30,184,36,36},//UITSTSSUV_DISPLAY_AREA_BACK,
	{174,184,36,36},//UITSTSSUV_DISPLAY_AREA_OK,
};

void ui_ts_tire_select_suv_enter(void)
{
	
}

void ui_ts_tire_select_suv_exit(void)
{
	
}

void ui_ts_tire_select_suv_show(void)
{
	static uint8_t index_01 = 0;
	static uint8_t index_02 = 0;
	
	draw_icon(&uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_SUV_BODY], ICON_ID_TP_CAR_BODY);
	
	draw_icon(&uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_TIRE_01], ICON_ID_TP_CAR_SUV_V_TIRE_RED + index_01);
	draw_icon(&uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_TIRE_01_CIRCLE], ICON_ID_TS_CIRCLE_DARK_GRAY);

	draw_icon(&uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_TIRE_02], ICON_ID_TP_CAR_SUV_V_TIRE_RED + index_01);
	draw_icon(&uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_TIRE_02_CIRCLE], ICON_ID_TS_CIRCLE_BLUE);

	draw_icon(&uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_TIRE_03], ICON_ID_TP_CAR_SUV_V_TIRE_RED + index_01);
	draw_icon(&uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_TIRE_03_CIRCLE], ICON_ID_TS_CIRCLE_DARK_GRAY);

	draw_icon(&uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_TIRE_04], ICON_ID_TP_CAR_SUV_V_TIRE_RED + index_01);
	draw_icon(&uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_TIRE_04_CIRCLE], ICON_ID_TS_CIRCLE_BLUE);

		draw_icon(&uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_TIRE_05], ICON_ID_TP_CAR_SUV_H_TIRE_RED + index_01);
	draw_icon(&uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_TIRE_05_CIRCLE], ICON_ID_TS_CIRCLE_BLUE);

	draw_icon(&uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_BACK], ICON_ID_TS_BACK_SELECT + index_02);
	draw_icon(&uitsts_suv_display_area[UITSTSSUV_DISPLAY_AREA_OK], ICON_ID_TS_OK_SELECT + index_02);

	if(++index_01 == 3)
	{
		index_01 = 0;
	}

	if(++index_02 == 2)
	{
		index_02 = 0;
	}
}

void ui_ts_tire_select_suv_init(void)
{
	
}
