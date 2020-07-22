#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_delay.h"
#include "drv_lis3dh.h"

#define G_SENSOR_MOSI_PIN_NUMBER  	26
#define G_SENSOR_CS_PIN_NUMBER	    28
#define G_SENSOR_SCLK_PIN_NUMBER	25
#define G_SENSOR_MISO_PIN_NUMBER	27

#define	G_SENSOR_SPI_CS_SET			nrf_gpio_pin_set(G_SENSOR_CS_PIN_NUMBER);
#define	G_SENSOR_SPI_CS_CLR			nrf_gpio_pin_clear(G_SENSOR_CS_PIN_NUMBER);

#define	G_SENSOR_SPI_MOSI_SET		nrf_gpio_pin_set(G_SENSOR_MOSI_PIN_NUMBER);		
#define	G_SENSOR_SPI_MOSI_CLR		nrf_gpio_pin_clear(G_SENSOR_MOSI_PIN_NUMBER);

#define	G_SENSOR_SPI_SCLK_SET		nrf_gpio_pin_set(G_SENSOR_SCLK_PIN_NUMBER);	
#define	G_SENSOR_SPI_SCLK_CLR		nrf_gpio_pin_clear(G_SENSOR_SCLK_PIN_NUMBER);

uint8_t lis3dh_raw_data_buffer[LIS3DH_RAW_DATA_BUFFER_SIZE];
AxesRaw_t lis3dh_axes_raw_data_buffer[LIS3DH_FIFO_DEPTH];

uint8_t gb_fss;

uint8_t lis3dh_spi_send_byte(uint8_t data)
{
	uint8_t i;
	for(i = 0; i < 8; i++)
	{
		if(0x80 & data) //MSB bit is transfered first
		{
			G_SENSOR_SPI_MOSI_SET;
		}
		else 
		{
			G_SENSOR_SPI_MOSI_CLR;
		}
		G_SENSOR_SPI_SCLK_CLR;
		nrf_delay_us(10);
		//临时将delay的时间从100改成2
		//cpu_delay(100);
		G_SENSOR_SPI_SCLK_SET;
		nrf_delay_us(5);
		data <<= 1;
		if(nrf_gpio_pin_read(G_SENSOR_MISO_PIN_NUMBER))
		{
			data++;
		}
	}
	return data;
}

static uint8_t lis3dh_spi_read(uint8_t address)
{
	uint8_t data;
	G_SENSOR_SPI_CS_CLR
	lis3dh_spi_send_byte(0x80 | address);
	data = lis3dh_spi_send_byte(0x00);
	G_SENSOR_SPI_CS_SET
	return data;
}


void lis3dh_handle_fifo_data(void)
{
	UTCTimeStruct time;
	ConvertUTCTime(&time, Get_Clock());

	for(uint8_t index = 0; index < gb_fss; index++)
	{
		//1.feed data to algorithm
		if(senssun_algorithm_0x01_feed_data(time.hour, time.minute, lis3dh_axes_raw_data_buffer[index].AXIS_X, lis3dh_axes_raw_data_buffer[index].AXIS_Y, lis3dh_axes_raw_data_buffer[index].AXIS_Z, 0) == 1)
		{
			static uint32_t wrist_list_count = 0;

			wrist_list_count++;

			USER_LOG_INFO("wrist_list_count = %d\r\n", wrist_list_count);
		}
		//2.send g sensor raw data to collector through ble or uart!!!
	}
}

void lis3dh_read_fifo_data()
{
	uint8_t index;
	uint8_t fss;
	uint8_t ovrun;

	LIS3DH_GetFifoSourceBit(LIS3DH_FIFO_SRC_OVRUN, ovrun);
	LIS3DH_GetFifoSourceFSS(&fss);

	if(MEMS_SET == ovrun)
	{
		fss = LIS3DH_FIFO_DEPTH;
	}
	
	fss = (fss >> 2) << 2;
	
	//USER_LOG_INFO("u8Ovrun = %d, u8Fss = %d\r\n", u8Ovrun, u8Fss);
	for(index = 0; index < fss; index++)
	{
		 LIS3DH_GetAccAxesRaw(lis3dh_axes_raw_data_buffer + index);  
	}

	gb_fss = fss;

	lis3dh_handle_fifo_data();
}

void lis3dh_register_check(void)
{
	uint8_t u8RegisterValue;
	u8RegisterValue = SPI_Mems_Read_Reg(0x20);
	USER_LOG_INFO("0x20 = 0x%02x\r\n", u8RegisterValue);

	u8RegisterValue = SPI_Mems_Read_Reg(0x22);
	USER_LOG_INFO("0x22 = 0x%02x\r\n", u8RegisterValue);

	u8RegisterValue = SPI_Mems_Read_Reg(0x23);
	USER_LOG_INFO("0x23 = 0x%02x\r\n", u8RegisterValue);

	u8RegisterValue = SPI_Mems_Read_Reg(0x24);
	USER_LOG_INFO("0x24 = 0x%02x\r\n", u8RegisterValue);

	u8RegisterValue = SPI_Mems_Read_Reg(0x25);
	USER_LOG_INFO("0x25 = 0x%02x\r\n", u8RegisterValue);

	u8RegisterValue = SPI_Mems_Read_Reg(0x26);
	USER_LOG_INFO("0x26 = 0x%02x\r\n", u8RegisterValue);

	u8RegisterValue = SPI_Mems_Read_Reg(0x2E);
	USER_LOG_INFO("0x2E = 0x%02x\r\n", u8RegisterValue);
}


void lis3dh_reboot_memory_content(void)
{
	USER_LOG_INFO("\r\n");
	SPI_Mems_Write_Reg(LIS3DH_CTRL_REG5, LIS3DH_BOOT);
	lis3dh_register_check();
}

static void lis3dh_mode_set(uint8_t mode)
{
	switch(mode)
	{
		case LIS3DH_OPERATION_MODE_NORMAL:
				lis3dh_reboot_memory_content();
				SPI_Mems_Write_Reg(0x20, 0x37);//25HZ, 使能x,y,z轴
				//SPI_Mems_Write_Reg(0x20, 0x27);//25HZ, 使能x,y,z轴
				SPI_Mems_Write_Reg(0x23, 0x08);//+-2G,High resolution Enable
				SPI_Mems_Write_Reg(0x2E, 0x80);//Stream Mode, 
				SPI_Mems_Write_Reg(0x24, 0x40);//FIFO Enable, 
	
				lis3dh_reboot_memory_content();

	/*初始化完后，首先是想办法清空G-Sensor FiFo Buffer里的数据*/
	prvLis3dhReadFifoData(NULL, 0);//Attention Please
			break;
    	case LIS3DH_OPERATION_MODE_LOW_POWER:
			break;
		default:
			break;
	}
}

static void lis3dh_spi_init(void)
{
	nrf_gpio_cfg_output(G_SENSOR_MOSI_PIN_NUMBER);
	nrf_gpio_cfg_output(G_SENSOR_CS_PIN_NUMBER);
	nrf_gpio_cfg_output(G_SENSOR_SCLK_PIN_NUMBER);
	nrf_gpio_cfg_input(G_SENSOR_MISO_PIN_NUMBER, NRF_GPIO_PIN_PULLUP);
    
    nrf_gpio_pin_set(G_SENSOR_MOSI_PIN_NUMBER);
    nrf_gpio_pin_set(G_SENSOR_CS_PIN_NUMBER);
    nrf_gpio_pin_set(G_SENSOR_SCLK_PIN_NUMBER);   
}

void who_am_i_check(void)
{
	uint8_t i;
	uint8_t who_am_i;

	who_am_i = lis3dh_spi_read(LIS3DH_WHO_AM_I);	
    NRF_LOG_INFO("who_am_i:%d\r\n", who_am_i);
}

void drv_lis3dh_init(void)
{
	lis3dh_spi_init();
	who_am_i_check();

	//Start a timer to read g sensor data!!!	
}
