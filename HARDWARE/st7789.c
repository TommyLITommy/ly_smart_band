#include "sdk_common.h"

#include "nrf_drv_spi.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"

#include "st7789.h"

#define ST7789_DC_PIN		13
#define ST7789_RES_PIN		14
#define ST7789_BLK_PIN		15
#define ST7789_CLK_PIN		12
#define ST7789_MISO_PIN     4
#define ST7789_MOSI_PIN		11
#define ST7789_SS_PIN       3

#define ST7789_DC_CLR()		nrf_gpio_pin_clear(ST7789_DC_PIN)
#define ST7789_DC_SET()		nrf_gpio_pin_set(ST7789_DC_PIN);
#define ST7789_RES_CLR() 	nrf_gpio_pin_clear(ST7789_RES_PIN)
#define ST7789_RES_SET()	nrf_gpio_pin_set(ST7789_RES_PIN)
#define ST7789_BLK_CLR()	nrf_gpio_pin_clear(ST7789_BLK_PIN)
#define ST7789_BLK_SET()	nrf_gpio_pin_set(ST7789_BLK_PIN)

#define ST7789_SPI_INSTANCE 0

#define USE_HORIZONTAL 0

static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(ST7789_SPI_INSTANCE);  /**< SPI instance. */

static inline void spi_write(const void*data, size_t size)
{
	APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, data, size, NULL, 0));
}

static inline void write_command(uint8_t c)
{
	ST7789_DC_CLR();
	spi_write(&c, sizeof(c));
}

static inline void write_data(uint8_t c)
{
	ST7789_DC_SET();
	spi_write(&c, sizeof(c));
}

static inline void write_data_16(uint16_t data)
{
	ST7789_DC_SET();
    const uint8_t buffer[2] = {data >> 8, data};
	spi_write(buffer, sizeof(buffer));
}

static void command_list(void)
{	    
	ST7789_RES_CLR();
	nrf_delay_ms(100);
	ST7789_RES_SET();
	nrf_delay_ms(100);
	
	ST7789_BLK_SET();
    nrf_delay_ms(100);
	
	//************* Start Initial Sequence **********//
	write_command(0x11); //Sleep out 
	nrf_delay_ms(120);              //Delay 120ms 
	//************* Start Initial Sequence **********// 
	write_command(0x36);
	if(USE_HORIZONTAL==0)write_data(0x00);
	else if(USE_HORIZONTAL==1)write_data(0xC0);
	else if(USE_HORIZONTAL==2)write_data(0x70);
	else write_data(0xA0);

	write_command(0x3A); 
	write_data(0x05);

	write_command(0xB2);
	write_data(0x0C);
	write_data(0x0C);
	write_data(0x00);
	write_data(0x33);
	write_data(0x33); 

	write_command(0xB7); 
	write_data(0x35);  

	write_command(0xBB);
	write_data(0x19);

	write_command(0xC0);
	write_data(0x2C);

	write_command(0xC2);
	write_data(0x01);

	write_command(0xC3);
	write_data(0x12);   

	write_command(0xC4);
	write_data(0x20);  

	write_command(0xC6); 
	write_data(0x0F);    

	write_command(0xD0); 
	write_data(0xA4);
	write_data(0xA1);

	write_command(0xE0);
	write_data(0xD0);
	write_data(0x04);
	write_data(0x0D);
	write_data(0x11);
	write_data(0x13);
	write_data(0x2B);
	write_data(0x3F);
	write_data(0x54);
	write_data(0x4C);
	write_data(0x18);
	write_data(0x0D);
	write_data(0x0B);
	write_data(0x1F);
	write_data(0x23);

	write_command(0xE1);
	write_data(0xD0);
	write_data(0x04);
	write_data(0x0C);
	write_data(0x11);
	write_data(0x13);
	write_data(0x2C);
	write_data(0x3F);
	write_data(0x44);
	write_data(0x51);
	write_data(0x2F);
	write_data(0x1F);
	write_data(0x1F);
	write_data(0x20);
	write_data(0x23);
	write_command(0x21); 

	write_command(0x29);
}

static void set_addr_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	ASSERT(x1 <= x2);
	ASSERT(y1 <= y2);
	
	if(USE_HORIZONTAL == 0)
	{
		write_command(0x2a);
		write_data_16(x1);
		write_data_16(x2);
		write_command(0x2b);
		write_data_16(y1);
		write_data_16(y2);
		write_command(0x2c);
	}
	else if(USE_HORIZONTAL == 1)
	{
		write_command(0x2a);
		write_data_16(x1);
		write_data_16(x2);
		write_command(0x2b);
		write_data_16(y1+80);
		write_data_16(y2+80);
		write_command(0x2c);
	}
	else if(USE_HORIZONTAL == 2)
	{
		write_command(0x2a);
		write_data_16(x1);
		write_data_16(x2);
		write_command(0x2b);
		write_data_16(y1);
		write_data_16(y2);
		write_command(0x2c);
	}
	else
	{
		write_command(0x2a);
		write_data_16(x1+80);
		write_data_16(x2+80);
		write_command(0x2b);
		write_data_16(y1);
		write_data_16(y2);
		write_command(0x2c);
	}
}

void st7789_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
	set_addr_window(x, y, x, y);
	
	const uint8_t data[2] = {color >> 8, color};
	
	ST7789_DC_SET();
	
	spi_write(data, sizeof(data));
	
	ST7789_DC_CLR();
}

void st7789_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	int32_t dx = x2 - x1;
	int32_t dy = y2 - y1;
	int32_t ux = ((dx > 0) << 1) - 1;
	int32_t uy = ((dy > 0) << 1) - 1;
	int	x = x1, y = y1, eps;
	eps = 0;
	dx  = abs(dx);
	dy  = abs(dy);
	if(dx > dy)
	{
		for(x = x1; x != x2; x += ux)
		{
			st7789_draw_pixel(x, y, color);
			eps += dy;
			if((eps << 1) >= dx)
			{
				y 	+= uy;
				eps -= dx;
			}
		}
	}
	else
	{
		for(y = y1; y != y2; y += uy)
		{
			st7789_draw_pixel(x, y, color);
			eps += dx;
			if((eps << 1) >= dy)
			{
				x  	+= ux;
				eps -= dy;
			}
		}
	}
}

void st7789_draw_picture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t *pic)
{
	uint16_t i,j,k=0;

	set_addr_window(x, y, x + length - 1, y + width - 1);

	ST7789_DC_SET();
	for(i = 0; i < length; i++)
	{
		for(j = 0; j < width; j++)
		{
			//LCD_WR_DATA8(pic[k*2]);
			//LCD_WR_DATA8(pic[k*2+1]);
			spi_write(&pic[k * 2], sizeof(pic[k * 2]));//Pay More Attention Here!
			spi_write(&pic[k * 2 + 1], sizeof(pic[k * 2 + 1]));
			k++;
		}
	}		
	ST7789_DC_CLR();
}

#if 0
void st7789_draw_picture_from_flash(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint32_t icon_flash_address)
{
	uint8_t buffer[240 * 2];
	uint32_t total_size;
	uint32_t index = 0;
	uint32_t read_size;
	total_size = length * width * 2;
	set_addr_window(x, y, x + length - 1, y + width - 1);
	
	ST7789_DC_SET();

	while(index < total_size)
	{
		if((index + 240 * 2) < total_size)
		{
			read_size = 240 * 2;
		}
		else
		{
			read_size = total_size - index;
		}

		extern void drv_flash_read(uint32_t address, uint8_t *p_buffer, uint32_t length);
		drv_flash_read(address + index, buffer, read_size);

		index += read_size;

		for(uint16_t i = 0; i < read_size; i++)
		{
			spi_write(&buffer[i], sizeof(buffer[i]));
		}		
	}
	
	ST7789_DC_CLR();
}
#endif

void st7789_fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	uint16_t i, j;
	
	const uint8_t data[2] = {color >> 8, color};
	
	set_addr_window(x1, y1, x2 - 1, y2 - 1);
	
    ST7789_DC_SET();
    
	for(i = y1; i < y2; i++)
	{
		for(j = x1; j < x2; j++)
		{
			spi_write(data, sizeof(data));
			//ST7789_DC_CLR();
		}
	}
    
    ST7789_DC_CLR();
}

static ret_code_t hardware_init(void)
{
	ret_code_t err_code;
	
	nrf_gpio_cfg_output(ST7789_DC_PIN);
    nrf_gpio_cfg_output(ST7789_RES_PIN);
    nrf_gpio_cfg_output(ST7789_BLK_PIN);
	
	nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
	
	spi_config.sck_pin 	= ST7789_CLK_PIN;
	spi_config.miso_pin = ST7789_MISO_PIN;
	spi_config.mosi_pin = ST7789_MOSI_PIN;
	spi_config.ss_pin	= ST7789_SS_PIN;
    
    spi_config.frequency = NRF_DRV_SPI_FREQ_8M;
	
	err_code = nrf_drv_spi_init(&spi, &spi_config, NULL, NULL);
	return err_code;
}

void st7789_init(void)
{
	ret_code_t err_code;
	
	err_code = hardware_init();
	APP_ERROR_CHECK(err_code);
	command_list();
}
