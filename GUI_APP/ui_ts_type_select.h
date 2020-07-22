#ifndef __UI_TS_TYPE_SELECT_H__
#define __UI_TS_TYPE_SELECT_H__

enum
{
	UITSTS_DISPLAY_AREA_MOTOR_ICON = 0,
	UITSTS_DISPLAY_AREA_MOTOR_NAME,
	UITSTS_DISPLAY_AREA_CAR_ICON,
	UITSTS_DISPLAY_AREA_CAR_NAME,
	UITSTS_DISPLAY_AREA_SUV_ICON,
	UITSTS_DISPLAY_AREA_SUV_NAME,
	UITSTS_DISPLAY_AREA_MAX
};

extern void ui_ts_type_select_enter(void);
extern void ui_ts_type_select_exit(void);
extern void ui_ts_type_select_show(void);
extern void ui_ts_type_select_init(void);

#endif

