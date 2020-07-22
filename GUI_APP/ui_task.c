#include "FreeRTOS.h"
#include "task.h"
#include "ui_main.h"
#include "ui_analog_clock.h"
#include "ui_notification.h"
#include "ui_heart_rate_measure.h"
#include "ui_blood_pressure_measure.h"
#include "ui_charging.h"
#include "ui_tire_setting.h"
#include "ui_ts_type_select.h"
#include "ui_ts_tire_select_motor.h"
#include "ui_ts_tire_select_car.h"
#include "ui_ts_tire_select_suv.h"
#include "ui_ts_tire_binding.h"
#include "ui_tp_motor.h"
#include "ui_tp_car.h"
#include "ui_tp_suv.h"
#include "ui_task.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

static ui_t ui_new = UI_TS_TIRE_BINDING;
static ui_t show_ui = UI_TS_TIRE_BINDING;
//static ui_t ui_new = UI_CHARGING;
//static ui_t show_ui = UI_CHARGING;

ui_show_func_t ui_show_func[UI_MAX] = 
{
	ui_main_show,
	ui_analog_clock_show,
	ui_charging_show,
	ui_notification_show,
	ui_heart_rate_measure_show,
	ui_blood_pressure_measure_show,
	ui_tire_setting_show,
	ui_ts_type_select_show,
	ui_ts_tire_select_motor_show,
	ui_ts_tire_select_car_show,
	ui_ts_tire_select_suv_show,
	ui_ts_tire_binding_show,
	ui_tp_motor_show,
	ui_tp_car_show,
	ui_tp_suv_show,
};

ui_enter_func_t ui_enter_func[UI_MAX] =
{
	ui_main_enter,
	ui_analog_clock_enter,
	ui_charging_enter,
	ui_notification_enter,
	ui_heart_rate_measure_enter,
	ui_blood_pressure_measure_enter,
	ui_tire_setting_enter,
	ui_ts_type_select_enter,
	ui_ts_tire_select_motor_enter,
	ui_ts_tire_select_car_enter,
	ui_ts_tire_select_suv_enter,
	ui_ts_tire_binding_enter,
	ui_tp_motor_enter,
	ui_tp_car_enter,
	ui_tp_suv_enter,
};

ui_exit_func_t ui_exit_func[UI_MAX] =
{
	ui_main_exit,
	ui_analog_clock_exit,
	ui_charging_exit,
	ui_notification_exit,
	ui_heart_rate_measure_exit,
	ui_blood_pressure_measure_exit,
	ui_tire_setting_exit,
	ui_ts_type_select_exit,
	ui_ts_tire_select_motor_exit,
	ui_ts_tire_select_car_exit,
	ui_ts_tire_select_suv_exit,
	ui_ts_tire_binding_exit,
	ui_tp_motor_exit,
	ui_tp_car_exit,
	ui_tp_suv_exit,
};

void ui_enter(ui_t ui)
{
	if(ui_enter_func[(uint8_t)ui] != NULL)
	{
		ui_enter_func[(uint8_t)ui]();
	}
}

void ui_exit(ui_t ui)
{
	if(ui_exit_func[(uint8_t)ui] != NULL)
	{
		ui_exit_func[(uint8_t)ui]();
	}
}

void set_show_ui(ui_t ui)
{
	//ui_exit(show_ui);
	ui_new = ui;
	//ui_enter(show_ui);
}

void ui_next(void)
{
	uint8_t ui_index;

	ui_index = (uint8_t)ui_new;

	if(++ui_index == (uint8_t)UI_MAX)
	{
		ui_index = (uint8_t)UI_MAIN;
	}

	ui_new = (ui_t)ui_index;
}

void ui_task(void *param)
{
	while(1)
	{
		if(ui_new != show_ui)
		{
			ui_exit(show_ui);
			show_ui = ui_new;
			ui_enter(show_ui);
		}
	
		#if 1
		if(ui_show_func[(uint8_t)show_ui] != NULL)
		{
			//NRF_LOG_INFO("show_ui:", (uint8_t)show_ui);
			ui_show_func[(uint8_t)show_ui]();
		}
		#else
		switch(show_ui)
		{
			case UI_MAIN:
				ui_main_show();
				break;
			case UI_ANALOG_CLOCK:
				break;
			case UI_CHARGING:
				break;
            case UI_NOTIFICATION:
                ui_notification_show();
                break;
			case UI_HEART_RATE_MEASURE:
				ui_heart_rate_measure_show();
				break;
			default:
				break;
		}
		#endif
	}
}

void ui_init(void)
{
	ui_main_init();
	ui_analog_clock_init();
    ui_notification_init();
	ui_heart_rate_measure_init();
	ui_charging_init();
}
