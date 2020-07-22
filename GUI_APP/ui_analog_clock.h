#ifndef __UI_ANALOG_CLOCK_H__
#define __UI_ANALOG_CLOCK_H__

typedef enum
{
	UIAC_DISPLAY_DIAL = 0,
	UIAC_DISPLAY_DATE,
	UIAC_DISPLAY_HAND_HOUR,
	UIAC_DISPLAY_HAND_MINUTE,
	UIAC_DISPLAY_AREA_MAX
}uiac_display_area_t;

#define PI 3.1415926
#define PI_DIV_180 (PI / 180)
#define DEG_TO_RAD(x) ((x) * PI_DIV_180)
#define MINUTE_HAND_LENGTH	110
#define HOUR_HAND_LENGTH	12

#define ANALOG_CLOCK_ORIGINAL_X   (120)
#define ANALOG_CLOCK_ORIGINAL_Y   (120)

extern void draw_clock(void);
extern void ui_analog_clock_enter(void);
extern void ui_analog_clock_exit(void);
extern void ui_analog_clock_show(void);
extern void ui_analog_clock_init(void);

#endif
