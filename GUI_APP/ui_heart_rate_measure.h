#ifndef __UI_HEART_RATE_MEASURE_H__
#define __UI_HEART_RATE_MEASURE_H__

enum
{
	UIHR_DISPLAY_AREA_HEART_RATE_ICON = 0,
	UIHR_DISPLAY_AREA_MEASURED_VALUE,
	UIHR_DISPLAY_AREA_UNIT,
	UIHR_DISPLAY_AREA_MAX
};

extern void ui_heart_rate_measure_enter(void);
extern void ui_heart_rate_measure_exit(void);
extern void ui_heart_rate_measure_show(void);
extern void ui_heart_rate_measure_init(void);

#endif
