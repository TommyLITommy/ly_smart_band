#ifndef __UI_TP_MOTOR_H__
#define __UI_TP_MOTOR_H__

enum
{
	UITPMOTOR_DISPLAY_AREA_MOTOR_BODY = 0,
	UITPMOTOR_DISPLAY_AREA_TIRE_01_TP,
	UITPMOTOR_DISPLAY_AREA_TIRE_01_TT,
	UITPMOTOR_DISPLAY_AREA_TIRE_02_TP,
	UITPMOTOR_DISPLAY_AREA_TIRE_02_TT,
	UITPMOTOR_DISPLAY_AREA_MAX
};

extern void ui_tp_motor_enter(void);
extern void ui_tp_motor_exit(void);
extern void ui_tp_motor_show(void);
extern void ui_tp_motor_init(void);

#endif
