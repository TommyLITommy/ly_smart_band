#ifndef __HEART_RATE_DATA_HANDLE_H__
#define __HEART_RATE_DATA_HANDLE_H__

#include <stdint.h>

typedef enum
{
	HAVE_PULSE_WAVE = 0x00,//有脉搏波
	NO_PULSE_WAVE = 0x01, //没有脉搏波
	WAVE_SATURATION = 0x02,//波形饱和
	NO_WEAR = 0x03,//没有佩戴上
}HEART_RATE_SIGNAL_STATUS_T;

extern uint8_t GetHeartRateValue(void);
extern uint8_t CalHeartRateValue(uint16_t uAdcData);
extern uint8_t GetSignalsState(void);
extern void clear_heart_rate_data_handle_para(void);
extern void whether_saturation_is_saturated(uint16_t source_data);
extern void smooth_heart_rate_data(uint32_t index, uint32_t *windows, uint32_t source_data);
extern void diff(uint32_t index, uint32_t *windows, uint32_t source_data);
extern void detect( uint16_t source_data,uint32_t buf_len, int32_t *p_buf, uint32_t n);
extern uint8_t GetHeartRateValue(void);
extern uint8_t GetSignalsState(void);
extern uint8_t CalBloodpressureValue(void);
extern uint8_t Get_PPG_Ps_Pd(void)	;
extern uint8_t GetBloodpressure_PS_Value(void);
extern uint8_t GetBloodpressure_PD_Value(void);

#endif
