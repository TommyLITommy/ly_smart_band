#ifndef __LY_LOG_H__
#define __LY_LOG_H__

#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#include "ly_log_config.h"

#ifndef LY_LOG_MODULE_NAME
	#define LY_LOG_MODULE_NAME ""
#endif

#define LY_LOG_BREAK ":"

#define LY_LOG_PREFIX LY_LOG_MODULE_NAME LY_LOG_BREAK

extern void log_info(char *fmt, ...);
//extern void log_hexdump(const uint8_t *p_data, uint16_t length);
extern void log_hexdump(const void * const p_data, uint8_t length);
extern void log_raw(char *fmt, ...);

#if LY_LOG_ENABLED

#define LY_LOG_INFO(format, ...) 																	\
	if(LY_LOG_LEVEL)																		\
	{																						\
		log_info(LY_LOG_PREFIX"func:%s,line:%d,"format, __FUNCTION__, __LINE__, ##__VA_ARGS__);	\
	}

#define LY_LOG_HEXDUMP(p_data, len)	\
	if(LY_LOG_LEVEL)                  \
	{									\
		log_hexdump(p_data, len);		\
	}


#define LY_LOG_RAW(format, ...) 				\
	if(LY_LOG_LEVEL)					\
	{									\
		log_raw(format, ##__VA_ARGS__);			\
	}

#else

#define LY_LOG_INFO(format, ...) 																	
#define LY_LOG_HEXDUMP(p_data, len)	
#define LY_LOG_RAW(format, ...) 				

#endif

#endif
