#ifndef __LY_BLE_P_H__
#define __LY_BLE_P_H__

#include "ly_ble.h"
#include "ble_db_discovery.h"

typedef struct
{
	on_ble_evt on_ble_peripheral_evt;
}ly_ble_p_t;

extern uint16_t latest_conn_handle;

extern void adv_start(void * p_context);
extern void ly_ble_p_db_disc_handler(ble_db_discovery_evt_t * p_evt);
extern void ly_ble_p_status_print(void);
extern void ly_ble_p_send_data_to_remote(uint16_t conn_handle, uint8_t *p_data, uint16_t length);
extern void ly_ble_p_init(ly_ble_p_t *p_ly_ble_p);

#endif
