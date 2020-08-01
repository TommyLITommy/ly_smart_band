#ifndef __GET_ICON_DATA_FROM_PC_H__
#define __GET_ICON_DATA_FROM_PC_H__

#include "type.h"

enum
{
	GET_ICON_DATA_FROM_PC_THROUGH_UART = 0,
	GET_ICON_DATA_FROM_PC_THROUGH_BLE,
};

extern void get_icon_data_from_pc_init(void);
extern void get_icon_data_from_pc(uint32_t offset, uint8_t *p_data_buffer, uint16_t data_length, uint8_t method);

#endif
