#ifndef __LY_BLE_P_H__
#define __LY_BLE_P_H__

#include "ble_gap.h"
#include "ly_ble.h"
#include "ble_db_discovery.h"

#define EXECUTING_ASYNCHRONOUS_COMMAND_MAX_COUNT 	4

typedef struct
{
	on_ble_evt on_ble_peripheral_evt;
}ly_ble_p_t;

typedef struct
{
	uint8_t group_id;
	uint8_t command_t;
}ly_ble_p_command_t;

typedef struct
{
	uint16_t 		conn_handle;
	ble_gap_addr_t  peer_addr; 
	ly_ble_p_command_t executing_asynchronous_command[EXECUTING_ASYNCHRONOUS_COMMAND_MAX_COUNT];
}ly_ble_p_central_info_t;

extern uint16_t latest_conn_handle;

extern void adv_start(void * p_context);
extern void ly_ble_p_db_disc_handler(ble_db_discovery_evt_t * p_evt);
extern void ly_ble_p_status_print(void);
extern void ly_ble_p_send_data_to_remote(uint16_t conn_handle, uint8_t *p_data, uint16_t length);
extern void ly_ble_p_init(ly_ble_p_t *p_ly_ble_p);

#endif
