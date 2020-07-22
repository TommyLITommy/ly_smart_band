#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "nrf_drv_wdt.h"
#include "nrf_drv_clock.h"
#include "global_config.h"

#include "watch_dog.h"

#define WATCH_DOG_RELOAD_VALUE  (20 * 1000)//20s

nrf_drv_wdt_channel_id m_channel_id;

void wdt_event_handler(void)
{		
	NRF_BREAKPOINT_COND;
}

void watch_dog_feed(void)
{
	nrf_drv_wdt_channel_feed(m_channel_id);
}

void watch_dog_init(void)
{
    uint32_t err_code;
	//Configure WDT.
    nrf_drv_wdt_config_t config = NRF_DRV_WDT_DEAFULT_CONFIG;
	config.reload_value			= WATCH_DOG_RELOAD_VALUE;
    err_code = nrf_drv_wdt_init(&config, wdt_event_handler);
    APP_ERROR_CHECK(err_code);
    err_code = nrf_drv_wdt_channel_alloc(&m_channel_id);
    APP_ERROR_CHECK(err_code);
    nrf_drv_wdt_enable();
}
