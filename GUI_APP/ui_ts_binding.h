#ifndef __UI_TS_BINDING_H__
#define __UI_TS_BINDING_H__

#include "ly_event.h"

enum
{
	UITS_BINDING_DISPLAY_AREA_NAME,
	UITS_BINDING_DISPLAY_AREA_MAC_ADDRESS,
	UITS_BINDING_DISPLAY_AREA_BACK,
	UITS_BINDING_DISPLAY_AREA_OK,
	UITS_BINDING_DISPLAY_AREA_MAX
};

extern void ui_ts_binding_event_handler(ly_event_t ly_event);
extern void ui_ts_binding_enter(void);
extern void ui_ts_binding_exit(void);
extern void ui_ts_binding_show(void);
extern void ui_ts_binding_init(void);

#endif
