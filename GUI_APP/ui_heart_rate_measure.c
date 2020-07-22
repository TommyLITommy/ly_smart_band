#include "draw_common.h"
#include "ui_heart_rate_measure.h"
 
display_area_t uihr_display_area[UIHR_DISPLAY_AREA_MAX] =
{
	{53,23,134,134},//UIHR_DISPLAY_AREA_HEART_RATE_ICON
	{98,177,43,19},//UIHR_DISPLAY_AREA_MEASURED_VALUE
	{102,201,36,18}//UIHR_DISPLAY_AREA_UNIT
};

void ui_heart_rate_measure_enter(void)
{
	draw_icon(&uihr_display_area[UIHR_DISPLAY_AREA_HEART_RATE_ICON], ICON_ID_HEART_RATE_ICON);
	draw_icon(&uihr_display_area[UIHR_DISPLAY_AREA_UNIT], ICON_ID_HERAT_RATE_UNIT);
}


void ui_heart_rate_measure_exit(void)
{
	for(uint8_t i = (uint8_t)UIHR_DISPLAY_AREA_HEART_RATE_ICON; i < (uint8_t)UIHR_DISPLAY_AREA_UNIT; i++)
	{
		draw_rectangle(&uihr_display_area[i], 0x00);
	}
}


void ui_heart_rate_measure_show(void)
{
	draw_icon(&uihr_display_area[UIHR_DISPLAY_AREA_HEART_RATE_ICON], ICON_ID_HEART_RATE_ICON);
	draw_icon(&uihr_display_area[UIHR_DISPLAY_AREA_UNIT], ICON_ID_HERAT_RATE_UNIT);
}

void ui_heart_rate_measure_init(void)
{
}
