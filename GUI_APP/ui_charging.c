#include "draw_common.h"
#include "ui_charging.h"

const display_area_t uicg_display_area[UICG_DISPLAY_AREA_MAX] =
{
	{65,35,110,170},		//UICG_DISPLAY_AREA_CHARGING
};

void ui_charging_enter(void)
{
	draw_icon(&uicg_display_area[UICG_DISPLAY_AREA_CHARGING], ICON_ID_CHARGING_00);
}

void ui_charging_exit(void)
{
	for(uint8_t i = (uint8_t)UICG_DISPLAY_AREA_CHARGING; i < (uint8_t)UICG_DISPLAY_AREA_MAX; i++)
	{
		draw_rectangle(&uicg_display_area[i], 0x00);
	}
}

static uint8_t uicg_change = 1;
static uint8_t uicg_index = 0;

void ui_charging_change(void)
{
	uicg_change = 1;
}

void ui_charging_show(void)
{
	if(uicg_change)
	{
		//uicg_change = 0;

		//draw_icon(&uicg_display_area[UICG_DISPLAY_AREA_CHARGING], ICON_ID_CHARGING_01);

		#if 1
		draw_icon(&uicg_display_area[UICG_DISPLAY_AREA_CHARGING], ICON_ID_CHARGING_00 + uicg_index);

		if(++uicg_index == 5)
		{
			uicg_index = 0;
		}
		#endif
	}
}

void ui_charging_init(void)
{
	//ui_charging_enter();
}

