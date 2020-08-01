#include <math.h>
#include <acceleration_data_handle.h>

#define SMOOTH_WINDOW_SIZE					4
#define SMOOTH_WINDOW_BUFFER_SIZE 			32
#define SMOOTH_WINDOW_BUFFER_SIZE_MASK 		(SMOOTH_WINDOW_BUFFER_SIZE - 1)

#define CONSECUTIVE_WAVE_MIN_COUNT			10

acceleration_data_handle_result_t acceleration_data_handle_result;
wave_tread_t wave_trend;

uint32_t smooth_window_buffer[SMOOTH_WINDOW_BUFFER_SIZE] = {0};

uint32_t smooth_window_buffer_head;
uint32_t smooth_window_buffer_tail;


uint32_t current_point;
uint32_t last_point;
uint32_t last_peak_point;
uint32_t last_valley_point;
uint32_t consecutive_wave;
uint32_t threashold;
uint32_t amplitude;
uint32_t sum_amplitude;
uint32_t last_upward_amplitude;
uint32_t last_downward_amplitude;
uint32_t coefficient;
uint32_t valley_to_peak_time;
uint32_t peak_to_valley_time;

uint32_t smooth(uint32_t resultant_acceleration)
{
	uint8_t	i, index = 0;
	uint32_t sum = 0;
		
	smooth_window_buffer_tail = (smooth_window_buffer_tail + 1) & SMOOTH_WINDOW_BUFFER_SIZE_MASK;
	smooth_window_buffer_head = (smooth_window_buffer_head + 1) & SMOOTH_WINDOW_BUFFER_SIZE_MASK;
	smooth_window_buffer[smooth_window_buffer_head] = resultant_acceleration;
	
	index = smooth_window_buffer_tail;
	
	for(i = 0; i < SMOOTH_WINDOW_SIZE; i++)
	{
		sum += smooth_window_buffer[i];
		index = (index + 1) & SMOOTH_WINDOW_BUFFER_SIZE_MASK;
	}
	
	return sum / SMOOTH_WINDOW_SIZE;
}

void acceleration_data_handle(uint32_t x_axis, uint32_t y_axis, uint32_t z_axis)
{
	uint32_t resultant_acceleration;
	
	resultant_acceleration = sqrt(pow(x_axis, 2) + pow(x_axis, 2) + pow(x_axis, 2));
	
	resultant_acceleration = smooth(resultant_acceleration);

	if(last_point > current_point)
	{
		if(wave_trend == WAVE_TREND_UPWARD)//Inflection Point
		{
			last_peak = last_point;
			//To be continued
		}
		
		wave_trend = WAVE_TREND_DOWNWARD;
		
	}
	else if(last_point < current_point)
	{
		if(wave_trend == WAVE_TREND_DOWNWARD)
		{
			if(consecutive_wave > 0)
			{
				threashold = (coefficient * sum_amplitude) / consecutive_wave;
			}
			else
			{
				threashold = 1000;//Initial value, Need modify
			}
			
			if()
			{
				sum_amplitude 		= 0;
				consecutive_wave 	= 0;
				valley_to_peak_time = 0;
				last_valley_pont 	= last_point;
			}
			
			if((last_upward_amplitude > threashold && last_downward_amplitude > 1000) || (last_downward_amplitude > threashold && last_upward_amplitude > 1000))//1000 should modify
			{
				if()
				{
					if(last_upward_amplitude > last_downward_amplitude)
					{
						sum_amplitude += last_upward_amplitude;//What does this mean??? 
					}
					else
					{
						sum_amplitude += last_downward_amplitude;
					}
					
					number++;
					consecutive_wave++;
					if(consecutive_wave == CONSECUTIVE_WAVE_MIN_COUNT)
					{
						acceleration_data_handle_result.total_step += CONSECUTIVE_WAVE_MIN_COUNT;
					}
					
					if(consecutive_wave > CONSECUTIVE_WAVE_MIN_COUNT)
					{
						acceleration_data_handle_result.total_step++;
					}
					
					valley_to_peak_time = 0;
					
				}
				
				if(last_point < last_valley_point)
				{
					last_valley_point = last_point;
					
				}
			}
		
		}
	}
	
}

void acceleration_data_handle_result_get(acceleration_data_handle_result_t *p_result)
{
	p_result->total_step 	= acceleration_data_handle_result.total_step;
	p_result->wrist_status 	= acceleration_data_handle_result.wrist_status;
	p_result->sleep_status	= acceleration_data_handle_result.sleep_status;
}

void acceleration_data_handle_init(uint32_t sample_rate)
{
    #if 0
	acceleration_data_handle_result.total_step 	 = 0;
	acceleration_data_handle_result.wrist_status = WRIST_STATUS_NONE;
	acceleration_data_handle_result.sleep_status = SLEEP_STATUS_NONE;
	
	smooth_window_buffer_head = 0;
	smooth_window_buffer_tail = 0;
    #endif
}

