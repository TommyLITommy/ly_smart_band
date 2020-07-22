#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#include "SEGGER_RTT.h"

#include "user_log.h"

void log_info(char *fmt, ...)
{
	char log_buffer[512] = {0};

    va_list ap;
    va_start(ap, fmt);
    vsprintf(log_buffer, fmt, ap);

	NRF_LOG_RAW_INFO("%s", (uint32_t)log_buffer);
	
    va_end(ap);
}

//void log_hexdump(const uint8_t *p_data, uint16_t length)
void log_hexdump(const void * const p_data, uint8_t length)
{
	uint8_t *p = (uint8_t *)p_data;
	//NRF_LOG_HEXDUMP_INFO(p_data, length);
	for(uint16_t i = 0; i < length; i++)
	{
		if((i != 0) && ((i % 20) == 0))
		{
			NRF_LOG_RAW_INFO("\r\n");
		}
		NRF_LOG_RAW_INFO("%02x ", p[i]);
	}

	NRF_LOG_RAW_INFO("\r\n");
}

void log_raw(char *fmt, ...)
{
	char log_buffer[512] = {0};
	
    va_list ap;
    va_start(ap, fmt);
    vsprintf(log_buffer, fmt, ap);

	NRF_LOG_RAW_INFO("%s", (uint32_t)log_buffer);
	
    va_end(ap);
}


