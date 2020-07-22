#ifndef __UI_TASK_H__
#define __UI_TASK_H__

typedef enum
{
	UI_MAIN = 0,
	UI_ANALOG_CLOCK,
	UI_CHARGING,
    UI_NOTIFICATION,
    UI_HEART_RATE_MEASURE,
    UI_BLOOD_PRESSURE_MEASURE,
    UI_TIRE_SETTING,
    UI_TS_TYPE_SELECT,
    US_TS_TIRE_SELECT_MOTOR,
    US_TS_TIRE_SELECT_CAR,
    US_TS_TIRE_SELECT_SUV,
    UI_TS_TIRE_BINDING,
    UI_TP_MOTOR,
    UI_TP_CAR,
    UI_TP_SUV,
    UI_MAX
}ui_t;

typedef void(*ui_show_func_t)(void);
typedef void(*ui_enter_func_t)(void);
typedef void(*ui_exit_func_t)(void);

extern void ui_next(void);
extern void ui_task(void *param);
extern void set_show_ui(uint8_t ui);
extern void ui_init(void);

#endif
