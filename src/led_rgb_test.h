#ifndef WIFI_LED_MCP_INC_LED_H
#define WIFI_LED_MCP_INC_LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/kernel.h>
#include <stdint.h>
#include <stdbool.h>

#define LED_MAX 4

int is_strip_ready(void);
int update_strip(uint16_t *hue, uint8_t *r, uint8_t *g, uint8_t *b);

#ifdef __cplusplus
}
#endif

#endif /* WIFI_LED_MCP_INC_LED_H */
