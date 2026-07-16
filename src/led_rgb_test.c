/*
 * Copyright (c) 2017 Linaro Limited
 * Copyright (c) 2018 Intel Corporation
 * Copyright (c) 2024 TOKITA Hiroshi
 *
 * SPDX-License-Identifier: Apache-2.0
 */

 #include <zephyr/logging/log.h>

 LOG_MODULE_REGISTER(led_strip_sample, LOG_LEVEL_DBG);

#include <zephyr/kernel.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/util.h>

#define STRIP_NODE		DT_ALIAS(led_strip)

#if DT_NODE_HAS_PROP(DT_ALIAS(led_strip), chain_length)
#define STRIP_NUM_PIXELS	DT_PROP(DT_ALIAS(led_strip), chain_length)
#else
#error Unable to determine length of LED strip
#endif

#define RGB(_r, _g, _b) { .r = (_r), .g = (_g), .b = (_b) }

static struct led_rgb pixels[STRIP_NUM_PIXELS];

static const struct device *const strip = DEVICE_DT_GET(STRIP_NODE);

int is_strip_ready(void)
{
    if (!device_is_ready(strip)) {
        LOG_ERR("LED strip device not ready");
        return -ENODEV;
    }

    return 0;
}

static void hsv_to_rgb(uint16_t h, uint8_t *r, uint8_t *g, uint8_t *b)
{
	float hh = (h % 360) / 60.0f;
    int i = (int)hh;
    float ff = hh - i;
    float p = 0.0f;
    float q = 1.0f - ff;
    float t = ff;

    float rf, gf, bf;
    switch (i) {
        case 0: rf = 1; gf = t; bf = p; break;
        case 1: rf = q; gf = 1; bf = p; break;
        case 2: rf = p; gf = 1; bf = t; break;
        case 3: rf = p; gf = q; bf = 1; break;
        case 4: rf = t; gf = p; bf = 1; break;
        case 5:
        default: rf = 1; gf = p; bf = q; break;
    }
    *r = (uint8_t)(rf * CONFIG_SAMPLE_LED_BRIGHTNESS);
    *g = (uint8_t)(gf * CONFIG_SAMPLE_LED_BRIGHTNESS);
    *b = (uint8_t)(bf * CONFIG_SAMPLE_LED_BRIGHTNESS);
}

int update_strip(uint16_t *hue, uint8_t *r, uint8_t *g, uint8_t *b)
{
    hsv_to_rgb(*hue, r, g, b);

    uint8_t red, green, blue;
    red = *r;
    green = *g;
    blue = *b;

    for (int i = 0; i < STRIP_NUM_PIXELS; i++) {
        pixels[i].r = red;
        pixels[i].g = green;
        pixels[i].b = blue;
    }
    // LOG_INF("Hue %u => RGB %u,%u,%u", *hue, *r, *g, *b);

    return led_strip_update_rgb(strip, pixels, STRIP_NUM_PIXELS);
}
