#include "draw_common.h"
#include "ly_event.h"
#include "ui_ts_tire_binding.h"

const display_area_t uits_tire_binding_display_area[UITS_TIRE_BINDING_DISPLAY_AREA_MAX] =
{
	{80,30,71,18},//UITS_TIRE_BINDING_DISPLAY_AREA_NAME,
	{0,0,0,0},//UITS_TIRE_BINDING_DISPLAY_AREA_MAC_ADDRESS,
	{30,184,36,36},//UITS_TIRE_BINDING_DISPLAY_AREA_BACK,
	{174,184,36,36},//UITS_TIRE_BINDING_DISPLAY_AREA_OK,
};

void ui_ts_tire_binding_event_handler(ly_event_t ly_event)
{
	
}

void ui_ts_tire_binding_enter(void)
{
	
}

void ui_ts_tire_binding_exit(void)
{
	
}

void ui_ts_tire_binding_show(void)
{
	draw_icon(&uits_tire_binding_display_area[UITS_TIRE_BINDING_DISPLAY_AREA_NAME], ICON_ID_TS_TIRE_BINDING_NAME);
	draw_icon(&uits_tire_binding_display_area[UITS_TIRE_BINDING_DISPLAY_AREA_BACK], ICON_ID_TS_BACK_SELECT);
	draw_icon(&uits_tire_binding_display_area[UITS_TIRE_BINDING_DISPLAY_AREA_OK], ICON_ID_TS_OK_SELECT);
}

void ui_ts_tire_binding_init(void)
{
	
}

