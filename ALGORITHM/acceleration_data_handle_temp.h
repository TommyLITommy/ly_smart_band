#ifndef __ACCELEARTION_DATA_HANDLE_TEMP_H__
#define __ACCELEARTION_DATA_HANDLE_TEMP_H__

extern void acceleartion_data_handle(uint8_t hour, uint8_t minute,int16_t x_axis, int16_t y_axis, int16_t z_axis);
extern uint32_t acceleartion_data_handle_result_get(void);
extern void acceleration_data_handle_clear(void);
extern uint8_t sleep_data_handle_result_get(void);
extern uint8_t lift_the_wrist_result_get(void);
extern int32_t ctinu_wave;
extern uint32_t ave_peak_intv;
extern uint16_t tmp_peak_intv;
extern uint32_t xcount;
extern uint32_t ycount;
extern uint32_t zcount;
#endif
