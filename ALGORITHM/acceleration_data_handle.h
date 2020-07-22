#ifndef __ACCELERATION_DATA_HANDLE_H__
#define __ACCELERATION_DATA_HANDLE_H__

typedef enum
{
	WAVE_TREND_NONE = 0,
	WAVE_TREND_UPWARD,
	WAVE_TREND_DOWNWARD,
}wave_tread_t;

typedef enum
{
	WRIST_STATUS_NONOE = 0,
	WRIST_STATUS_WRIST_LIFT,
	WRIST_STATUS_WRIST_PUT_DOWN,
}wrist_status_t;

typedef enum
{
	SLEEP_STATUS_NONE = 0,
	SLEEP_STATUS_AWAKE,
	SLEEP_STATUS_SHALLOW_SLEEP,
	SLEEP_STATUS_DEEP_SLEEP,
}sleep_status_t;

typedef struct
{
	uint32_t total_step;
	uint8_t wrist_status;
	uint8_t sleep_status;
}acceleration_data_handle_result_t;

#endif