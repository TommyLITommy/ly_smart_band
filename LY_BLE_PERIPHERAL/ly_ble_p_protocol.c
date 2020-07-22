#include "sdk_common.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "ui_task.h"
#include "hardware.h"
#include "draw_common.h"
#include "ly_ble_p_protocol.h"

//Remote ble central send data to this handler
/*
	Functions:
		1.Erase (external or internal) flash by sector index(specific sector or the whole chip) through ble or uart!!!
		2.Flash (external or internal) flash by address with length
		3.Enable or disable log print
		4.Read sensor raw data(si11xx,ads129x,mems,env)
*/
void ly_ble_p_protocol_handler(const uint8_t *p_data, uint16_t length)
{
	if(length >= 1)
	{
		switch(p_data[0])
		{
			case 1:
				ui_next();
				NRF_LOG_INFO("Short Press");
				break;
			case 2:
				NRF_LOG_INFO("Long Press");
				break;
			case 3:
				NRF_LOG_INFO("Clear Screen");
				hardware.hal_lcd.lcd_fill(0, 0, 240, 240, BLACK);
				break;
			case 4:
				NRF_LOG_INFO("Reset");
				NVIC_SystemReset();
				break;
			default:
				break;
		}
	}
}

void ly_ble_p_protocol_init(void)
{
	
}
