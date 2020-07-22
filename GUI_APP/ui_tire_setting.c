#include "draw_common.h"
#include "ui_tire_setting.h"

const display_area_t uits_display_area[UITS_DISPLAY_AREA_MAX] =
{
	{43, 23, 158, 158},//UITS_DISPLAY_AREA_TIRE_SETTING_ICON
	{81, 191, 79, 20}//UITS_DISPLAY_AREA_TIRE_SETTING_NAME
};

void ui_tire_setting_enter(void)
{
	draw_icon(&uits_display_area[UITS_DISPLAY_AREA_TIRE_SETTING_ICON], ICON_ID_TIRE_SETTING_ICON);
	draw_icon(&uits_display_area[UITS_DISPLAY_AREA_TIRE_SETTING_NAME], ICON_ID_TIRE_SETTING_NAME);
}

void ui_tire_setting_exit(void)
{
	for(uint8_t i = (uint8_t)UITS_DISPLAY_AREA_TIRE_SETTING_ICON; i < (uint8_t)UITS_DISPLAY_AREA_MAX; i++)
	{
		draw_rectangle(&uits_display_area[i], 0x00);
	}
}

void ui_tire_setting_show(void)
{
	draw_icon(&uits_display_area[UITS_DISPLAY_AREA_TIRE_SETTING_ICON], ICON_ID_TIRE_SETTING_ICON);
	draw_icon(&uits_display_area[UITS_DISPLAY_AREA_TIRE_SETTING_NAME], ICON_ID_TIRE_SETTING_NAME);
}

void ui_tire_setting_init(void)
{
	
}
