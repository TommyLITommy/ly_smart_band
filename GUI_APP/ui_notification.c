#include "draw_common.h"
#include "ui_notification.h"

const display_area_t uintfn_display_area[UINTFN_DISPLAY_AREA_MAX] =
{
	{20,25,40,40},//UINTFN_DISPLAY_AREA_ICON_MESSAGE
	{10,20,220,50},//UINTFN_DISPLAY_AREA_ICON_OVAL_FRAME
	{33,90,0,0},//UINTFN_DISPLAY_AREA_NOTIFCATION_DETAIL
	{101,70,60,60}//UINTFN_DISPLAY_AREA_ICON_INCOMING_CALL
};

void ui_notification_enter(void)
{
	draw_icon(&uintfn_display_area[UINTFN_DISPLAY_AREA_ICON_OVAL_FRAME], ICON_ID_OVAL_FRAME_03);
	draw_icon(&uintfn_display_area[UINTFN_DISPLAY_AREA_ICON_MESSAGE], ICON_ID_QQ);
}

void ui_notification_exit(void)
{
	for(uint8_t i = (uint8_t)UINTFN_DISPLAY_AREA_ICON_MESSAGE; i < (uint8_t)UINTFN_DISPLAY_AREA_MAX; i++)
	{
		draw_rectangle(&uintfn_display_area[i], 0x00);
	}
}

static uint8_t index = 0;

void ui_notification_show(void)
{
	draw_icon(&uintfn_display_area[UINTFN_DISPLAY_AREA_ICON_OVAL_FRAME], ICON_ID_OVAL_FRAME_03);
	draw_chinese(178, 77, 0, 0, 0x001F);
	draw_icon(&uintfn_display_area[UINTFN_DISPLAY_AREA_ICON_MESSAGE], ICON_ID_QQ + index);
	if(++index == 3)
	{
		index = 0;
	}
}

void ui_notification_init(void)
{
	
}
