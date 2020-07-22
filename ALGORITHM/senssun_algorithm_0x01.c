#include <stdint.h>
#include <string.h>
#include "log_print.h"
#include "acceleration_data_handle_temp.h"
#include "senssun_algorithm_0x01.h"

static senssun_algorithm_0x01_result_t senssun_algorithm_0x01_result;

uint8_t senssun_algorithm_0x01_feed_data(uint8_t hour, uint8_t minute, uint16_t x_axis, uint16_t y_axis, uint16_t z_axis, uint8_t heart_rate)
{  
	acceleartion_data_handle(hour, minute, x_axis, y_axis, z_axis);
	senssun_algorithm_0x01_result.wrist_status = sleep_data_handle_result_get();
	senssun_algorithm_0x01_result.step = acceleartion_data_handle_result_get();	
	senssun_algorithm_0x01_result.wrist_lift_status = lift_the_wrist_result_get();
	return senssun_algorithm_0x01_result.wrist_lift_status;
	//log_print("wrist_lift_status = %d\r\n", senssun_algorithm_0x01_result.wrist_lift_status);
}
 
void senssun_algorithm_0x01_get_result(senssun_algorithm_0x01_result_t *p_senssun_algorithm_0x01_result)
{
	p_senssun_algorithm_0x01_result->wrist_status = senssun_algorithm_0x01_result.wrist_status;
	p_senssun_algorithm_0x01_result->wrist_lift_status 	= senssun_algorithm_0x01_result.wrist_lift_status;
	p_senssun_algorithm_0x01_result->step 							= senssun_algorithm_0x01_result.step;
}

void senssun_algorithm_0x01_step_reset(void)
{
	senssun_algorithm_0x01_result.step 	 = 0;
	acceleration_data_handle_clear();
}

void senssun_algorithm_0x01_init(void)
{
	senssun_algorithm_0x01_result.wrist_status   	   = WRIST_STATUS_NONE;
	senssun_algorithm_0x01_result.wrist_lift_status    = WRIST_LIFT_STATUS_NO;
	senssun_algorithm_0x01_result.step       		   = 0;
}

