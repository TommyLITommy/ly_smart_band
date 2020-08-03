#ifndef __LY_BLE_C_H__
#define __LY_BLE_C_H__

#include "ly_ble.h"
#include "ble_db_discovery.h"

#define EXECUTING_ASYNCHRONOUS_COMMAND_MAX_COUNT 	4

typedef struct
{
	on_ble_evt on_ble_central_evt;
}ly_ble_c_t;

typedef struct
{
	uint8_t group_id;
	uint8_t command_t;
}ly_ble_c_command_t;

typedef struct
{
	uint16_t 		conn_handle;
	ble_gap_addr_t  peer_addr; 
	ly_ble_c_command_t executing_asynchronous_command[EXECUTING_ASYNCHRONOUS_COMMAND_MAX_COUNT];
}ly_ble_c_peripheral_info_t;

extern void ly_ble_c_db_disc_handler(ble_db_discovery_evt_t * p_evt);
extern void scan_start(void);
extern void scan_stop(void);
extern void ly_ble_c_status_print(void);
extern void ly_ble_c_init(ly_ble_c_t *p_ly_ble_c);

#endif
