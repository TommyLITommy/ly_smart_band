#ifndef __UI_TIRE_SETTING_H__
#define __UI_TIRE_SETTING_H__

enum
{
	UITS_DISPLAY_AREA_TIRE_SETTING_ICON = 0,
	UITS_DISPLAY_AREA_TIRE_SETTING_NAME,
	UITS_DISPLAY_AREA_MAX
};

extern void ui_tire_setting_enter(void);
extern void ui_tire_setting_exit(void);
extern void ui_tire_setting_show(void);
extern void ui_tire_setting_init(void);

#endif
