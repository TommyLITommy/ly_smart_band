#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "ble_gattc.h"
#include "crc16.h"
#include "uart_protocol.h"
#include "ly_ble_p_protocol.h"
#include "ly_ble_c_protocol.h"

void ly_ble_c_protocol_handler(uint16_t conn_handle, const uint8_t *p_data, uint16_t length)
{
	uint16_t crc16_01 = 0, crc16_02 = 0;

	if(length < BLE_PROTOCOL_MIN_SIZE)
	{
		NRF_LOG_INFO("length < %d", BLE_PROTOCOL_MIN_SIZE);
		return;
	}
	
	crc16_01 += p_data[length - 2] << 0;
	crc16_01 += p_data[length - 1] << 8;

	crc16_02 = crc16_compute(p_data, length - 2, NULL);

	NRF_LOG_INFO("crc16_01:%d, crc16_02:%d", crc16_01, crc16_02);
	//if(crc16_01 != crc16_02)
	if(0)
	{	
		NRF_LOG_INFO("crc16 check error");
		return;
	}

	switch(p_data[BLE_PROTOCOL_GROUP_ID_FIELD_OFFSET])
	{
		case BLE_PROTOCOL_GROUP_ID_NONE:
			break;
		case BLE_PROTOCOL_GROUP_ID_SET:
			//ly_ble_p_protocol_gid_set_handler(conn_handle, p_data, length);
			break;
		case BLE_PROTOCOL_GROUP_ID_READ:
			//ly_ble_p_protocol_gid_read_handler(conn_handle, p_data, length);
			break;
		case BLE_PROTOCOL_GROUP_ID_ACTION:
			//ly_ble_p_protocol_gid_action_handler(conn_handle, p_data, length);
			break;
		case BLE_PROTOCOL_GROUP_ID_UPLOAD:
			//ly_ble_p_protocol_gid_upload_handler(conn_handle, p_data, length);
			break;
		case BLE_PROTOCOL_GROUP_ID_DEBUG:
			//ly_ble_p_protocol_gid_debug_handler(conn_handle, p_data, length);
			break;
		case BLE_PROTOCOL_GROUP_ID_FLASH:
			//ly_ble_p_protocol_gid_flash_handler(conn_handle, p_data, length);
			break;
		default:
			break;
	}
	NRF_LOG_INFO("\r\n");

	//conn_handle,mac_address,ble_protocol
	uint8_t buffer[10];
	uint16_t index = 0;
	buffer[index++] = BLE_GATTC_EVT_HVX;
	uint16_encode(conn_handle, &buffer[index]);
	index += 2;
	uint8_t mac_address[6] = {0xF1,0xF2,0xF3,0xF4,0xF5,0xF6};
	memcpy(&buffer[index], mac_address, 6);
	index += 6;
	memcpy(&buffer[index], p_data, length);
	index += length;
	uart_protocol_assemble_command_and_send(GROUP_ID_BLE_C, GID_BLE_P_CID_DTP_BLE_CENTTRAL_EVENT, buffer, index);
}


void ly_ble_c_protocol_init(void)
{
}
