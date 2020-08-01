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

#include "sys_malloc.h"
#include "sys_queue.h"
#include "sys_info.h"

#define SYSTEM_TIMER_INTERVAL         				1000  
#define BATTERY_LEVEL_MEAS_INTERVAL					100
#define HEART_RATE_MEAS_INTERVAL					100
#define STEP_COUNT_INTERVAL							100
#define MEMS_RAW_DATA_MEAS_INTERVAL			        200

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
static TimerHandle_t m_mems_raw_data_meas_timer;

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

//Tommy Debug, Very Important!!!!!!
//If the task never active release cpu resource, the idle hook will never be called!!!
//特别注意，如果没有system log打印，可能的原因是某个task没有释放cpu使用权，一直占着，这样导致logger task永远不会执行！！！
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

	NRF_LOG_INFO("system_running_time:%ld", system_running_time);

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
}

static void step_timer_timeout_handler(TimerHandle_t xTimer)
{
	system_running_time++;
}

uint8_t buffer[200] = {0x11, 0x22, 0x33};
static void mems_raw_data_meas_timeout_handler(TimerHandle_t xTimer)
{
	NRF_LOG_INFO("mems measure");
	ly_ble_p_send_data_to_remote(latest_conn_handle, buffer, sizeof(buffer));
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
	
	if(pdPASS != xTimerStart(m_mems_raw_data_meas_timer, OSTIMER_WAIT_FOR_QUEUE))
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
								   

	m_mems_raw_data_meas_timer = xTimerCreate("MEMS", 
								MEMS_RAW_DATA_MEAS_INTERVAL,
								pdTRUE,
								NULL,
								mems_raw_data_meas_timeout_handler);
								
	if((NULL == m_system_timer) ||
	   (NULL == m_battery_timer) ||
	   (NULL == m_heart_rate_timer) ||
	   (NULL == m_step_timer) ||
	   (NULL == m_mems_raw_data_meas_timer))
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

void uart_rx_command_handler(uint8_t *p_data, uint16_t length)
{
	
}

int main(void)
{	
    log_init();
	
    clock_init();

	timers_init();

    // Start execution.
    if (pdPASS != xTaskCreate(logger_thread, "LOGGER", 512, NULL, 1, &m_logger_thread))
    {
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }

	// Activate deep sleep mode.
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

	//#ifdef NRF52832_XXAA
    #if 1
	sys_malloc_init(&sys_info);
	sys_queue_init(&sys_info.rx_queue);
    
    sys_info_init(&sys_info);
    sys_info.hardware.drv_uart.drv_uart_rx_command_handler = uart_rx_command_handler;
	#endif

	#if 1
	ui_init();
	//xTaskCreate(start_task, "START_TASK", 300, NULL, 2, &start_task_handle);
	xTaskCreate(ui_task, "ui_task", 300, NULL, 1, &ui_task_handle);
	#endif

	#if 1
	ly_ble_init();

	nrf_sdh_freertos_init(adv_scan_start, NULL);

	NRF_LOG_INFO("FreeRTOS Start, Free Heap:%d bytes\r\n", xPortGetFreeHeapSize());
	#endif
	
	application_timers_start();

	vTaskStartScheduler();

	while(1)
	{
	
	}
}


