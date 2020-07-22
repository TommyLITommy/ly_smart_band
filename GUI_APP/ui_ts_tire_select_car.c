#include "draw_common.h"
#include "ui_ts_tire_select_car.h"

const display_area_t uitsts_car_display_area[UITSTSCAR_DISPLAY_AREA_MAX] =
{
	{72,20,96,180},//UITSTSCAR_DISPLAY_AREA_CAR_BODY
	{80,51,11,27},//UITSTSCAR_DISPLAY_AREA_TIRE_01
	{15,15,50,50},//UITSTSCAR_DISPLAY_AREA_TIRE_01_CIRCLE
	{149,51,11,27},//UITSTSCAR_DISPLAY_AREA_TIRE_02
	{175,20,50,50},//UITSTSCAR_DISPLAY_AREA_TIRE_02_CIRCLE
	{80,153,11,27},//UITSTSCAR_DISPLAY_AREA_TIRE_03
	{15,121,50,50},//UITSTSCAR_DISPLAY_AREA_TIRE_03_CIRCLE
	{148,153,11,27},//UITSTSCAR_DISPLAY_AREA_TIRE_04
	{175,121,50,50},//UITSTSCAR_DISPLAY_AREA_TIRE_04_CIRCLE
	{30,184,36,36},//UITSTSCAR_DISPLAY_AREA_BACK
	{174,184,36,36},//UITSTSCAR_DISPLAY_AREA_OK
};

void ui_ts_tire_select_car_enter(void)
{
	
}
void ui_ts_tire_select_car_exit(void)
{
	
}
void ui_ts_tire_select_car_show(void)
{
	static uint8_t index_01 = 0;
	static uint8_t index_02 = 0;
	
	draw_icon(&uitsts_car_display_area[UITSTSCAR_DISPLAY_AREA_CAR_BODY], ICON_ID_TP_CAR_BODY);
	
	draw_icon(&uitsts_car_display_area[UITSTSCAR_DISPLAY_AREA_TIRE_01], ICON_ID_TP_CAR_SUV_V_TIRE_RED + index_01);
	draw_icon(&uitsts_car_display_area[UITSTSCAR_DISPLAY_AREA_TIRE_01_CIRCLE], ICON_ID_TS_CIRCLE_DARK_GRAY);

	draw_icon(&uitsts_car_display_area[UITSTSCAR_DISPLAY_AREA_TIRE_02], ICON_ID_TP_CAR_SUV_V_TIRE_RED + index_01);
	draw_icon(&uitsts_car_display_area[UITSTSCAR_DISPLAY_AREA_TIRE_02_CIRCLE], ICON_ID_TS_CIRCLE_BLUE);

	draw_icon(&uitsts_car_display_area[UITSTSCAR_DISPLAY_AREA_TIRE_03], ICON_ID_TP_CAR_SUV_V_TIRE_RED + index_01);
	draw_icon(&uitsts_car_display_area[UITSTSCAR_DISPLAY_AREA_TIRE_03_CIRCLE], ICON_ID_TS_CIRCLE_DARK_GRAY);

	draw_icon(&uitsts_car_display_area[UITSTSCAR_DISPLAY_AREA_TIRE_04], ICON_ID_TP_CAR_SUV_V_TIRE_RED + index_01);
	draw_icon(&uitsts_car_display_area[UITSTSCAR_DISPLAY_AREA_TIRE_04_CIRCLE], ICON_ID_TS_CIRCLE_BLUE);

	draw_icon(&uitsts_car_display_area[UITSTSCAR_DISPLAY_AREA_BACK], ICON_ID_TS_BACK_SELECT + index_02);
	draw_icon(&uitsts_car_display_area[UITSTSCAR_DISPLAY_AREA_OK], ICON_ID_TS_OK_SELECT + index_02);

	if(++index_01 == 3)
	{
		index_01 = 0;
	}

	if(++index_02 == 2)
	{
		index_02 = 0;
	}
}
void ui_ts_tire_select_car_init(void)
{
	
}
