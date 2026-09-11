#include "sdcard.h"

#include <driver/sdspi_host.h>
#include <esp_vfs_fat.h>
#include <sdmmc_cmd.h>

#include <esp_log.h>

const static char *TAG = "SDCARD";

esp_err_t sdcard_init(sdcard_api_t sdcard_api) {
	esp_err_t err;

	if (sdcard_api == SDCARD_API_SDSPI) {
		spi_bus_config_t bus_cfg = {
			.mosi_io_num = CONFIG_SDCARD_SDSPI_MOSI,
			.miso_io_num = CONFIG_SDCARD_SDSPI_MISO,
			.sclk_io_num = CONFIG_SDCARD_SDSPI_SCK,
			.quadhd_io_num = GPIO_NUM_NC,
			.quadwp_io_num = GPIO_NUM_NC,
		};

		sdmmc_host_t host = SDSPI_HOST_DEFAULT();

		err = spi_bus_initialize(host.slot, &bus_cfg, SDSPI_DEFAULT_DMA);
		if (err == ESP_ERR_INVALID_ARG) {
			ESP_LOGE(TAG,
					 "spi bus not initialized: configuration is invalid: %s",
					 esp_err_to_name(err));
			return err;
		} else if (err == ESP_ERR_INVALID_STATE) {
			ESP_LOGE(TAG, "spi bus not initialized: host already in use: %s",
					 esp_err_to_name(err));
			return err;
		} else if (err == ESP_ERR_NOT_FOUND) {
			ESP_LOGE(TAG,
					 "spi bus not initialized: no available DMA channel: %s",
					 esp_err_to_name(err));
			return err;
		} else if (err == ESP_ERR_NO_MEM) {
			ESP_LOGE(TAG, "spi bus not initialized: out of memory: %s",
					 esp_err_to_name(err));
			return err;
		}

		sdspi_device_config_t sdspi_dev_cfg = SDSPI_DEVICE_CONFIG_DEFAULT();
		sdspi_dev_cfg.gpio_cs = CONFIG_SDCARD_SDSPI_CS;
		sdspi_dev_cfg.host_id = host.slot;

		esp_vfs_fat_sdmmc_mount_config_t mount_cfg = {
			.format_if_mount_failed = true,
			.max_files = CONFIG_SDCARD_MAX_FILES,
		};

		sdmmc_card_t *card;

		err = esp_vfs_fat_sdspi_mount("/" CONFIG_SDCARD_MOUNT_PATH, &host,
									  &sdspi_dev_cfg, &mount_cfg, &card);
		if (err == ESP_ERR_INVALID_ARG) {
			ESP_LOGE(TAG, "mount card failed: required arg is null: %s",
					 esp_err_to_name(err));
			return err;
		} else if (err == ESP_ERR_INVALID_STATE) {
			ESP_LOGE(TAG, "mount card failed: was already called: %s",
					 esp_err_to_name(err));
			return err;
		} else if (err == ESP_ERR_NO_MEM) {
			ESP_LOGE(TAG, "mount card failed: memory can not be allocated: %s",
					 esp_err_to_name(err));
			return err;
		} else if (err == ESP_FAIL) {
			ESP_LOGE(TAG, "mount card failed: partition can not be mounted: %s",
					 esp_err_to_name(err));
			return err;
		} else if (err != ESP_OK) {
			ESP_LOGE(TAG, "mount card failed: other error: %s",
					 esp_err_to_name(err));
			return err;
		}

		sdmmc_card_print_info(stdout, card);
	} else { // SDCARD_API_SDMMC
			 // todo
	}

	return ESP_OK;
}
