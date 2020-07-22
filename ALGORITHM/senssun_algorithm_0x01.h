#ifndef __SENSSUN_ALGORITHM_0X01_H__
#define __SENSSUN_ALGORITHM_0X01_H__
#include <stdint.h>
#include <string.h>
typedef enum
{
	WRIST_STATUS_NONE = 0,
	WRIST_STATUS_STEP,
	WRIST_STATUS_LIGHT_SLEEP,
	WRIST_STATUS_DEEP_SLEEP,
}wrist_status_t;

typedef enum
{
	WRIST_LIFT_STATUS_NO = 0,
	WRIST_LIFT_STATUS_YES,
}wrist_lift_status_t;

typedef struct
{
	uint8_t wrist_status;
	uint8_t wrist_lift_status;
	uint32_t step;
}senssun_algorithm_0x01_result_t;

extern uint8_t senssun_algorithm_0x01_feed_data(uint8_t hour, uint8_t minute, uint16_t x_axis, uint16_t y_axis, uint16_t z_axis, uint8_t heart_rate);
extern void senssun_algorithm_0x01_get_result(senssun_algorithm_0x01_result_t *p_senssun_algorithm_0x01_result);
extern void senssun_algorithm_0x01_step_reset(void);
extern void senssun_algorithm_0x01_init(void);

#endif
