#ifndef COMPONENT_SDCARD_H
#define COMPONENT_SDCARD_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { SDCARD_API_SDSPI, SDCARD_API_SDMMC } sdcard_api_t;

esp_err_t sdcard_init();

#ifdef __cplusplus
}
#endif

#endif // COMPONENT_SDCARD_H
