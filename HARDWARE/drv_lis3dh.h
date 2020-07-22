#ifndef __DRV_LIS3DH__H__
#define __DRV_LIS3DH__H__

#define LIS3DH_RAW_DATA_BUFFER_SIZE    	192
#define LIS3DH_FIFO_DEPTH 				32
#define LIS3DH_WHO_AM_I					0x0F

enum
{
	LIS3DH_OPERATION_MODE_NORMAL,
    LIS3DH_OPERATION_MODE_LOW_POWER,
};

extern void who_am_i_check(void);
extern void drv_lis3dh_init(void);

#endif
