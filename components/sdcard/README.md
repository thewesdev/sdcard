# SD Card

## Features

* SD card initialization
* SDSPI interface support
* FAT filesystem mounting
* Configurable SPI pins via menuconfig
* Configurable mount path via menuconfig
* Optional C++ wrapper

## SDSPI

| Parameter | Default |
| --------- | ------- |
| MOSI      | GPIO 4  |
| MISO      | GPIO 5  |
| SCK       | GPIO 3  |
| CS        | GPIO 48 |

## SDMMC

**Not implemented yet.**

## Menuconfig

```bash
idf.py menuconfig
```

### Path

Component config -> SDCARD

### Default Configs

#### SDSPI

| SDCARD   | Type     | Macro                    | Values |
| -------- | -------- | ------------------------ | ------ |
| SPI MOSI | GPIO_NUM | CONFIG_SDCARD_SDSPI_MOSI | 4      |
| SPI MISO | GPIO_NUM | CONFIG_SDCARD_SDSPI_MISO | 5      |
| SPI SCK  | GPIO_NUM | CONFIG_SDCARD_SDSPI_SCK  | 3      |
| SPI CS   | GPIO_NUM | CONFIG_SDCARD_SDSPI_CS   | 48     |

#### General

| Configuration | Type   | Macro                    | Values |
| ------------- | ------ | ------------------------ | ------ |
| Mount path    | string | CONFIG_SDCARD_MOUNT_PATH | sdcard |
| Max files     | int    | CONFIG_SDCARD_MAX_FILES  | 1      |

## Installation

### IDF Component Registry

```bash
idf.py add-dependency thewesdev/sdcard
```

For update newest versions:

```bash
idf.py update-dependencies
```

### Github

```bash
git clone https://github.com/thewesdev/sdcard
```

## API

### C

```c
#include "sdcard.h"

esp_err_t sdcard_init(sdcard_api_t sdcard_api);
```

### C++

```cpp
#include "sdcard.hpp"

esp_err_t sdcard::init(sdcard_api_t sdcard_api);
```

## Supported APIs

```c
typedef enum {
    SDCARD_API_SDSPI,
    SDCARD_API_SDMMC
} sdcard_api_t;
```

Currently, only `SDCARD_API_SDSPI` is implemented.

## Code Examples

### C

```c
#include "sdcard.h"

void app_main(void)
{
    sdcard_init(SDCARD_API_SDSPI);
}
```

### C++

```cpp
#include "sdcard.hpp"

extern "C" void app_main(void)
{
    sdcard::init(SDCARD_API_SDSPI);
}
```

After successful initialization, the SD card is mounted at the configured mount path.

With the default configuration:

```text
/sdcard
```

The FAT filesystem can then be accessed using standard file I/O functions:

```c
FILE *file = fopen("/sdcard/test.txt", "w");

if (file != NULL) {
    fprintf(file, "Hello, SD card!\n");
    fclose(file);
}
```

## Notes

* `SDCARD_API_SDSPI` uses the ESP-IDF SDSPI host driver.
* The SPI bus is initialized by the component.
* The FAT filesystem is mounted automatically during initialization.
* `SDCARD_API_SDMMC` is reserved for future implementation.
* `format_if_mount_failed` is currently enabled, so the filesystem may be formatted if mounting fails.
