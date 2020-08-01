#ifndef __UI_SCAN_DEVICE_H__
#define __UI_SCAN_DEVICE_H__

#include "ly_event.h"

extern void ui_scan_device_event_handler(ly_event_t ly_event);
extern void ui_scan_device_enter(void);
extern void ui_scan_device_exit(void);
extern void ui_scan_device_show(void);
extern void ui_scan_device_init(void);

#endif
