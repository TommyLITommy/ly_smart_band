#ifndef __TOUCH_KEY_H__
#define __TOUCH_KEY_H__

typedef enum
{
	TOUCH_KEY_STATUS_RELEASE = 0,
	TOUCH_KEY_STATUS_DOWN,
}touch_key_status_t;

#define TOUCH_KEY_JITTER_TICKS 				10//Need modify
#define TOUCH_KEY_LONG_PRESS_TICKS   		50

extern void touch_key_uninit(void);
extern void touch_key_init(void);

#endif

