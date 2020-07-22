#ifndef __UI_BLOOD_PRESSURE_MEASURE_H__
#define __UI_BLOOD_PRESSURE_MEASURE_H__

enum
{
	UIBD_DISPLAY_AREA_BP_ICON,
	UIBD_DISPLAY_AREA_MEASURED_DATA,
	UIBD_DISPLAY_AREA_UNIT,
	UIBD_DISPLAY_AREA_MAX,
};

extern void ui_blood_pressure_measure_enter(void);
extern void ui_blood_pressure_measure_exit(void);
extern void ui_blood_pressure_measure_show(void);
extern void ui_blood_pressure_measure_init(void);

#endif
