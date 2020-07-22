#include <stdint.h>
#include "nrf_drv_gpiote.h"
#include "nrf_gpio.h"
#include "app_error.h"

#include "task.h"
#include "boards.h"
#include "touch_key.h"

static uint8_t touch_key_status;
static uint32_t key_down_timestamp;
static uint32_t key_release_timestamp;

static void touch_key_interrupt_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	uint32_t value;

	//print action value

	value = nrf_gpio_pin_read(TOUCH_KEY_PRESS_DETECT_PIN_NUMBER);

	if(value == 0)
	{
		touch_key_status = TOUCH_KEY_STATUS_DOWN;
		key_down_timestamp = xTaskGetTickCount();
	}
	else
	{
		key_release_timestamp = xTaskGetTickCount();

		if(touch_key_status == TOUCH_KEY_STATUS_DOWN)
		{
			touch_key_status = TOUCH_KEY_STATUS_RELEASE;

			if(key_release_timestamp > key_down_timestamp)
			{
				uint32_t delta;
				delta = key_release_timestamp - key_down_timestamp;

				if(delta < TOUCH_KEY_JITTER_TICKS)
				{
				}
				else if(delta >= TOUCH_KEY_JITTER_TICKS && delta < TOUCH_KEY_LONG_PRESS_TICKS)
				{
					//Short Press
				}
				else
				{
					//Long Press
				}
			}
		}
	}
}

static void touch_key_interrupt_init(void)
{
	ret_code_t err_code;
	nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_TOGGLE;
	
	if(!nrf_drv_gpiote_is_init())
	{
		err_code = nrf_drv_gpiote_init();
		APP_ERROR_CHECK(err_code);
	}
	
	in_config.pull = NRF_GPIO_PIN_PULLUP;
	err_code = nrf_drv_gpiote_in_init(TOUCH_KEY_PRESS_DETECT_PIN_NUMBER, &in_config, touch_key_interrupt_handler);
	APP_ERROR_CHECK(err_code);
	
	nrf_drv_gpiote_in_event_enable(TOUCH_KEY_PRESS_DETECT_PIN_NUMBER, true);
}

void touch_key_uninit(void)
{
	nrf_drv_gpiote_in_event_disable(TOUCH_KEY_PRESS_DETECT_PIN_NUMBER);
	nrf_drv_gpiote_in_uninit(TOUCH_KEY_PRESS_DETECT_PIN_NUMBER);
	nrf_gpiote_event_clear(NRF_GPIOTE_EVENTS_PORT);
}

void touch_key_init(void)
{
	nrf_gpio_cfg_output(TOUCH_KEY_POWER_SUPPLY_PIN_NUMBER);
	nrf_gpio_pin_set(TOUCH_KEY_POWER_SUPPLY_PIN_NUMBER);
	touch_key_interrupt_init();
}