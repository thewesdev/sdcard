#ifndef COMPONENT_SDCARD_HPP
#define COMPONENT_SDCARD_HPP

#include "sdcard.h"

namespace sdcard {
	inline esp_err_t init() { return sdcard_init(); }
} // namespace sdcard

#endif
