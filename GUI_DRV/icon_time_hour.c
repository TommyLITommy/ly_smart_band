#include <stdio.h>
#include <stdlib.h>
#if 1
#define icon_time_hour_00 NULL
#define icon_time_hour_01 NULL
#define icon_time_hour_02 NULL
#define icon_time_hour_03 NULL
#define icon_time_hour_04 NULL
#define icon_time_hour_05 NULL
#define icon_time_hour_06 NULL
#define icon_time_hour_07 NULL
#define icon_time_hour_08 NULL
#define icon_time_hour_09 NULL
#else
extern const unsigned char icon_time_hour_00[11284];
extern const unsigned char icon_time_hour_01[11284]; 
extern const unsigned char icon_time_hour_02[11284]; 
extern const unsigned char icon_time_hour_03[11284]; 
extern const unsigned char icon_time_hour_04[11284]; 
extern const unsigned char icon_time_hour_05[11284]; 
extern const unsigned char icon_time_hour_06[11284]; 
extern const unsigned char icon_time_hour_07[11284]; 
extern const unsigned char icon_time_hour_08[11284]; 
extern const unsigned char icon_time_hour_09[11284]; 
#endif
const unsigned char *icon_time_hour[10] =
{
	icon_time_hour_00,
	icon_time_hour_01,
	icon_time_hour_02,
	icon_time_hour_03,
	icon_time_hour_04,
	icon_time_hour_05,
	icon_time_hour_06,
	icon_time_hour_07,
	icon_time_hour_08,
	icon_time_hour_09
};
