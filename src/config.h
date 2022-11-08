#ifndef CONFIG_H
#define CONFIG_H

#include "Arduino.h"
#include "sensor.h"

#define LED_BUILTIN 2

const char *VERSION = "3.0.0";

// Modifying the config version will probably cause a loss of the existig configuration.
// Be careful!
const char *CONFIG_VERSION = "1.0.2";

static const SensorConfig SENSOR_CONFIGS[] = {
    {.pin = 14,
     .name = "1",
     .numeric_only = false,
     .status_led_enabled = true,
     .status_led_inverted = true,
     .status_led_pin = LED_BUILTIN,
     .interval = 0}};

const uint8_t NUM_OF_SENSORS = sizeof(SENSOR_CONFIGS) / sizeof(SensorConfig);

#endif