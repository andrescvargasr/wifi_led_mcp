/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

 #include <errno.h>
#include <string.h>

#include "led_rgb_test.h"

#define LOG_LEVEL 4
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

#define DELAY_TIME K_MSEC(CONFIG_SAMPLE_LED_UPDATE_DELAY)

int main(void)
{
	int ret;

	ret = is_strip_ready();
	if (ret) {
		LOG_ERR("LED strip not ready");
		return ret;
	}

	uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint16_t hue = 0; /* angle 0..359 */

	for(;;) {
		ret = update_strip(&hue, &red, &green, &blue);
		if (ret) {
			LOG_ERR("couldn't update strip: %d", ret);
		}

		hue = (hue + 1) % 360;
		k_sleep(DELAY_TIME);
	}

	return 0;
}
