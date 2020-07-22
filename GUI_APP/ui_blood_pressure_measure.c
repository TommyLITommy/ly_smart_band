#include "draw_common.h"
#include "ui_blood_pressure_measure.h"

static display_area_t uibp_display_area[UIBD_DISPLAY_AREA_MAX] = 
{
	{53,23,134,134},//UIBD_DISPLAY_AREA_BP_ICON
	{77,174,88,25},//UIBD_DISPLAY_AREA_MEASURED_DATA
	{96,204,51,18}//UIBD_DISPLAY_AREA_UNIT
};

void ui_blood_pressure_measure_enter(void)
{
	draw_icon(&uibp_display_area[UIBD_DISPLAY_AREA_BP_ICON], ICON_ID_BLOOD_PRESSURE_ICON);
	draw_icon(&uibp_display_area[UIBD_DISPLAY_AREA_UNIT], ICON_ID_BLOOD_PRESSURE_UNIT);
}

void ui_blood_pressure_measure_exit(void)
{
	for(uint8_t i = (uint8_t)UIBD_DISPLAY_AREA_BP_ICON; i < (uint8_t)UIBD_DISPLAY_AREA_MAX; i++)
	{
		draw_rectangle(&uibp_display_area[i], 0x00);
	}
}

void ui_blood_pressure_measure_show(void)
{
	draw_icon(&uibp_display_area[UIBD_DISPLAY_AREA_BP_ICON], ICON_ID_BLOOD_PRESSURE_ICON);
	draw_icon(&uibp_display_area[UIBD_DISPLAY_AREA_UNIT], ICON_ID_BLOOD_PRESSURE_UNIT);
}

void ui_blood_pressure_measure_init(void)
{
	
}