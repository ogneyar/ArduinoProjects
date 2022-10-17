#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

#define PIN_LED1 12
#define PIN_LED2 13

void app_main() {
  gpio_set_direction(PIN_LED1, GPIO_MODE_OUTPUT);
  gpio_set_direction(PIN_LED2, GPIO_MODE_OUTPUT);
  gpio_set_level(PIN_LED2, 0);
  while (1) {
    gpio_set_level(PIN_LED1, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_set_level(PIN_LED1, 1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}