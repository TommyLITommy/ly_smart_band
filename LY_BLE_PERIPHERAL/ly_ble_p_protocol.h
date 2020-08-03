#ifndef __LY_BLE_P_PROTOCOL_H__
#define __LY_BLE_P_PROTOCOL_H__

#define BLE_PROTOCOL_MIN_SIZE						7

#define BLE_PROTOCOL_SEQUENCE_FIELD_OFFSET 			0
#define BLE_PROTOCOL_GROUP_ID_FIELD_OFFSET			1
#define BLE_PROTOCOL_COMMAND_ID_FIELD_OFFSET		2
#define BLE_PROTOCOL_PAYLOAD_LENGTH_FIELD_OFFSET	3
#define BLE_PROTOCOL_PAYLOAD_OFFSET					5

typedef enum
{
	BLE_PROTOCOL_GROUP_ID_NONE = 0x00,
	BLE_PROTOCOL_GROUP_ID_SET,
	BLE_PROTOCOL_GROUP_ID_READ,
	BLE_PROTOCOL_GROUP_ID_ACTION,
	BLE_PROTOCOL_GROUP_ID_UPLOAD,
	BLE_PROTOCOL_GROUP_ID_DEBUG = 0x06,
	BLE_PROTOCOL_GROUP_ID_FLASH = 0x07,
}ble_protocol_gid_id_t;

typedef enum
{
	BLE_PROTOCOL_GROUP_SET_CID_0x01 = 0x01,//enable or disable mems or ecg ppg data upload, payload format:type, on/off
}ble_protocol_group_set_cid_t;

typedef enum
{
	BLE_PROTOCOL_GROUP_READ_CID_0x01 = 0x01,
}ble_protocol_group_read_cid_t;

typedef enum
{
	BLE_PROTOCOL_GROUP_ACTION_CID_0x01 = 0x01,
}ble_protocol_group_action_cid_t;

typedef enum
{
	BLE_PROTOCOL_GROUP_UPLOAD_CID_1_AXIS = 0x01,
	BLE_PROTOCOL_GROUP_UPLOAD_CID_3_AXIS,
	BLE_PROTOCOL_GROUP_UPLOAD_CID_6_AXIS,
	BLE_PROTOCOL_GROUP_UPLOAD_CID_9_AXIS,
	BLE_PROTOCOL_GROUP_UPLOAD_CID_PPG,//ppg
	BLE_PROTOCOL_GROUP_UPLOAD_CID_ECG,//ecg 
}ble_protocol_group_upload_cid_t;
	
typedef enum
{
	BLE_PROTOCOL_GID_DEBUG_CID_SHORT_PRESS,
	BLE_PROTOCOL_GID_DEBUG_CID_LONG_PRESS,
	BLE_PROTOCOL_GID_DEBUG_CID_SYSTEM_RESET,
	BLE_PROTOCOL_GID_DEBUG_CID_DATABASE_DISCOVERY,
}ble_protocol_gid_debug_cid_t;

typedef enum
{
	BLE_PROTOCOL_GID_FLASH_CID_ERASE = 0,
	BLE_PROTOCOL_GID_FLASH_CID_WRITE,
	BLE_PROTOCOL_GID_FLASH_CID_READ,
}ble_protocol_gid_flash_cid_t;

enum
{	
	FLASH_ID_INTERNAL = 0,
	FLASH_ID_EXTERNAL,
};
	
extern void ly_ble_p_protocol_handler(uint16_t conn_handle, const uint8_t *p_data, uint16_t length);

#endif
