#include "draw_common.h"
#include "ui_ts_type_select.h"

const display_area_t uitsts_display_area[UITSTS_DISPLAY_AREA_MAX] =
{
	{30,12,64,64},//UITSTS_DISPLAY_AREA_MOTOR_ICON
	{114,36,59,20},//UITSTS_DISPLAY_AREA_MOTOR_NAME
	{30,86,64,64},//UITSTS_DISPLAY_AREA_CAR_ICON
	{114,105,59,20},//UITSTS_DISPLAY_AREA_CAR_NAME
	{30,160,64,64},//UITSTS_DISPLAY_AREA_SUV_ICON
	{114,184,59,20},//UITSTS_DISPLAY_AREA_SUV_NAME
};

void ui_ts_type_select_enter(void)
{

}

void ui_ts_type_select_exit(void)
{
	
}

void ui_ts_type_select_show(void)
{
	draw_icon(&uitsts_display_area[UITSTS_DISPLAY_AREA_MOTOR_ICON], ICON_ID_CIRCLE_02_BLUE);
	draw_icon(&uitsts_display_area[UITSTS_DISPLAY_AREA_CAR_ICON], ICON_ID_CIRCLE_02_WHITE);
	draw_icon(&uitsts_display_area[UITSTS_DISPLAY_AREA_SUV_ICON], ICON_ID_CIRCLE_02_BLUE);
}

void ui_ts_type_select_init(void)
{
	
}
