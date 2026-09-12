#ifndef COMPONENT_SDCARD_HPP
#define COMPONENT_SDCARD_HPP

#include "sdcard.h"

namespace sdcard {
	inline esp_err_t init(sdcard_api_t sdcard_api) {
		return sdcard_init(sdcard_api);
	}
} // namespace sdcard

#endif
