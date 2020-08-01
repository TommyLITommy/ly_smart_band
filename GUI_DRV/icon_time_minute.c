#include <stdio.h>
#include <stdlib.h>
#if 1
#define icon_time_minute_00 NULL
#define icon_time_minute_01 NULL
#define icon_time_minute_02 NULL
#define icon_time_minute_03 NULL
#define icon_time_minute_04 NULL
#define icon_time_minute_05 NULL
#define icon_time_minute_06 NULL
#define icon_time_minute_07 NULL
#define icon_time_minute_08 NULL
#define icon_time_minute_09 NULL
#else
extern const unsigned char icon_time_minute_00[2436];
extern const unsigned char icon_time_minute_01[2436]; 
extern const unsigned char icon_time_minute_02[2436]; 
extern const unsigned char icon_time_minute_03[2436]; 
extern const unsigned char icon_time_minute_04[2436]; 
extern const unsigned char icon_time_minute_05[2436]; 
extern const unsigned char icon_time_minute_06[2436]; 
extern const unsigned char icon_time_minute_07[2436]; 
extern const unsigned char icon_time_minute_08[2436]; 
extern const unsigned char icon_time_minute_09[2436]; 
#endif

const unsigned char *icon_time_minute[10] =
{
	icon_time_minute_00,
	icon_time_minute_01,
	icon_time_minute_02,
	icon_time_minute_03,
	icon_time_minute_04,
	icon_time_minute_05,
	icon_time_minute_06,
	icon_time_minute_07,
	icon_time_minute_08,
	icon_time_minute_09,
};
