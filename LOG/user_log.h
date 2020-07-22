#ifndef __USER_LOG_H__
#define __USER_LOG_H__

#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#include "user_log_config.h"

#ifndef USER_LOG_MODULE_NAME
	#define USER_LOG_MODULE_NAME ""
#endif

#define USER_LOG_BREAK ":"

#define USER_LOG_PREFIX USER_LOG_MODULE_NAME USER_LOG_BREAK

extern void log_info(char *fmt, ...);
//extern void log_hexdump(const uint8_t *p_data, uint16_t length);
extern void log_hexdump(const void * const p_data, uint8_t length);
extern void log_raw(char *fmt, ...);

#if USER_LOG_ENABLED

#define USER_LOG_INFO(format, ...) 																	\
	if(USER_LOG_LEVEL)																		\
	{																						\
		log_info(USER_LOG_PREFIX"func:%s,line:%d,"format, __FUNCTION__, __LINE__, ##__VA_ARGS__);	\
	}

#define USER_LOG_HEXDUMP(p_data, len)	\
	if(USER_LOG_LEVEL)                  \
	{									\
		log_hexdump(p_data, len);		\
	}


#define USER_LOG_RAW(format, ...) 				\
	if(USER_LOG_LEVEL)					\
	{									\
		log_raw(format, ##__VA_ARGS__);			\
	}

#else

#define USER_LOG_INFO(format, ...) 																	
#define USER_LOG_HEXDUMP(p_data, len)	
#define USER_LOG_RAW(format, ...) 				

#endif

#endif
