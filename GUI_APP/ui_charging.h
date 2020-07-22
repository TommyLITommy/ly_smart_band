#ifndef __UI_CHARGING_H__
#define __UI_CHARGING_H__

typedef enum
{
	UICG_DISPLAY_AREA_CHARGING = 0,
	UICG_DISPLAY_AREA_MAX
}uicg_display_area_t;

extern void ui_charging_enter(void);
extern void ui_charging_exit(void);
extern void ui_charging_show(void);
extern void ui_charging_change(void);
extern void ui_charging_init(void);

#endif

