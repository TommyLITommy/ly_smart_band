#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
#include "nrf_sdh_freertos.h"
#include "app_error.h"
#include "app_timer.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "fds.h"
#include "ble_conn_state.h"
#include "nrf_drv_clock.h"
#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#include "nrf_fstorage.h"
#include "nrf_delay.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "ui_task.h"
#include "hardware.h"
#include "ui_main.h"
#include "ui_analog_clock.h"
#include "ui_charging.h"

#include "ly_ble.h"
#include "ly_ble_p.h"
#include "ly_ble_c.h"

#define SYSTEM_TIMER_INTERVAL         				1000  
#define BATTERY_LEVEL_MEAS_INTERVAL					1000
#define HEART_RATE_MEAS_INTERVAL					1000
#define STEP_COUNT_INTERVAL							1000

#define OSTIMER_WAIT_FOR_QUEUE              		2                                       /**< Number of ticks to wait for the timer queue to be ready */

//Task Handle
static TaskHandle_t m_logger_thread;                                
static TaskHandle_t start_task_handle;                                
static TaskHandle_t ui_task_handle;   

//Timer Handle
static TimerHandle_t m_system_timer; 
static TimerHandle_t m_battery_timer;
static TimerHandle_t m_heart_rate_timer;
static TimerHandle_t m_step_timer;

static uint32_t system_time;
static uint32_t system_running_time;

static void clock_init(void)
{
    ret_code_t err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);
}

static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

static void logger_thread(void * arg)
{
    UNUSED_PARAMETER(arg);

    while (1)
    {
        NRF_LOG_FLUSH();

        vTaskSuspend(NULL); // Suspend myself
    }
}

//If the task never active release cpu resource, the idle hook will never be called!!!

void vApplicationIdleHook( void )
{
    vTaskResume(m_logger_thread);
}

void start_task(void *param)
{
	taskENTER_CRITICAL();

	xTaskCreate(ui_task, "ui_task", 300, NULL, 3, &ui_task_handle);

	NRF_LOG_INFO("Free Heap:%d bytes\r\n", xPortGetFreeHeapSize());

    vTaskDelete(start_task_handle);
    
	taskEXIT_CRITICAL();
}

static void system_timer_timeout_handler(TimerHandle_t xTimer)
{
	static uint8_t i = (uint8_t)UI_MAIN;
    UNUSED_PARAMETER(xTimer);

	NRF_LOG_INFO("system_running_time:%ld\r\n", system_running_time);

	#if 1
    //set_show_ui(i);
	
	i = (i + 1);

	if(i == (uint8_t)UI_MAX)
	{
		i = (uint8_t)UI_MAIN;
	}

	system_time++;
	system_running_time++;
	#endif
}

static void battery_timer_timeout_handler(TimerHandle_t xTimer)
{
	system_running_time++;
}

static void heart_rate_timer_timeout_handler(TimerHandle_t xTimer)
{
	system_running_time++;
	//draw_clock();
	//ui_charging_change();
}

static void step_timer_timeout_handler(TimerHandle_t xTimer)
{
	system_running_time++;
}

static void application_timers_start(void)
{
	if(pdPASS != xTimerStart(m_system_timer, OSTIMER_WAIT_FOR_QUEUE))
	{
		APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
	}

	if(pdPASS != xTimerStart(m_battery_timer, OSTIMER_WAIT_FOR_QUEUE))
	{
		APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
	}

	if(pdPASS != xTimerStart(m_heart_rate_timer, OSTIMER_WAIT_FOR_QUEUE))
	{
		APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
	}

	if(pdPASS != xTimerStart(m_step_timer, OSTIMER_WAIT_FOR_QUEUE))
	{
		APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
	}
}

static void timers_init(void)
{
	ret_code_t err_code = app_timer_init();
	APP_ERROR_CHECK(err_code);

	m_system_timer = xTimerCreate("SYSTEM_TIME", 
								  SYSTEM_TIMER_INTERVAL,
								  pdTRUE,
								  NULL,
								  system_timer_timeout_handler);
								  
	m_battery_timer = xTimerCreate("BATT",
								   BATTERY_LEVEL_MEAS_INTERVAL,
								   pdTRUE,
								   NULL,
								   battery_timer_timeout_handler);

    m_heart_rate_timer = xTimerCreate("HR",
								   HEART_RATE_MEAS_INTERVAL,
								   pdTRUE,
								   NULL,
								   heart_rate_timer_timeout_handler);


    m_step_timer = xTimerCreate("STEP",
								STEP_COUNT_INTERVAL,
								pdTRUE,
                                NULL,
								step_timer_timeout_handler);
								   
								   
	if((NULL == m_system_timer) ||
	   (NULL == m_battery_timer) ||
	   (NULL == m_heart_rate_timer) ||
	   (NULL == m_step_timer))
	{
		APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
	}
}

static void adv_scan_start(void * p_context)
{
    ret_code_t err_code;

    //check if there are no flash operations in progress
    if (!nrf_fstorage_is_busy(NULL))//Tommy Debug, What is the purpose of this check?
    {
        // Start scanning for peripherals and initiate connection to devices which
        // advertise Heart Rate or Running speed and cadence UUIDs.
        //scan_start();
        adv_start(NULL);
    }
}

#if 0
int main(void)
{	
    log_init();
	
    clock_init();

	timers_init();
	
	hardware_init();

	ly_ble_init();

	adv_start(NULL);
	
	while(1)
	{
		NRF_LOG_FLUSH();
		nrf_delay_ms(1000);
		NRF_LOG_INFO("system_running_time:%d", system_running_time++);
	}
}

#else
int main(void)
{	
    log_init();
	
    clock_init();

	timers_init();

    // Start execution.
    if (pdPASS != xTaskCreate(logger_thread, "LOGGER", 256, NULL, 1, &m_logger_thread))
    {
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }

	// Activate deep sleep mode.
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

	#if 1
	hardware_init();

	ui_init();

	//{65,35,110,170},
	//extern const unsigned char icon_charging_01[];
	//hardware.hal_lcd.lcd_draw_picture(65,35,110,170,icon_charging_01);
	//ui_enter(UI_NOTIFICATION);
    //ui_task(NULL);
    
	//xTaskCreate(start_task, "START_TASK", 300, NULL, 2, &start_task_handle);
	xTaskCreate(ui_task, "ui_task", 300, NULL, 1, &ui_task_handle);
	#endif

	#if 0
	ly_ble_init();

	nrf_sdh_freertos_init(adv_scan_start, NULL);

	NRF_LOG_INFO("Tommy FreeRTOS example started.");
	#endif
	application_timers_start();

	vTaskStartScheduler();

	//It will never reach here!
	while(1)
	{
	
	}
}
#endif

