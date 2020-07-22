#ifndef __UI_TS_TIRE_SELECT_MOTOR_H__
#define __UI_TS_TIRE_SELECT_MOTOR_H__

enum
{
	UITSTSMOTOR_DISPLAY_AREA_MOTOR_BODY = 0,
	UITSTSMOTOR_DISPLAY_AREA_TIRE_01,
	UITSTSMOTOR_DISPLAY_AREA_TIRE_01_CIRCLE,
	UITSTSMOTOR_DISPLAY_AREA_TIRE_02,
	UITSTSMOTOR_DISPLAY_AREA_TIRE_02_CIRCLE,
	UITSTSMOTOR_DISPLAY_AREA_BACK,
	UITSTSMOTOR_DISPLAY_AREA_OK,
	UITSTSMOTOR_DISPLAY_AREA_MAX,
};

extern void ui_ts_tire_select_motor_enter(void);
extern void ui_ts_tire_select_motor_exit(void);
extern void ui_ts_tire_select_motor_show(void);
extern void ui_ts_tire_select_motor_init(void);

#endif
