#ifndef __GLOBAL_CONFIG_H__
#define __GLOBAL_CONFIG_H__

//#define ENABLE_PAIRING 

#define LY_LOG_MODULE_ENABLED(module) \
    ((defined(module ## _ENABLED) && (module ## _ENABLED)) ? 1 : 0)


#endif
