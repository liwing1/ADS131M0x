#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ads131m0x.h"
#include "hal.h"
#include "driver/ledc.h"

// Example pin, change as per your setup
#define PWM_PIN 21

void pwm_task(void *pvParameters) {
    // Configure PWM settings
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_3_BIT,
        .freq_hz = 8192000,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .channel = LEDC_CHANNEL_0,
        .duty = 4,
        .gpio_num = PWM_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER_0
    };
    ledc_channel_config(&ledc_channel);

    while (1) {
        // Your code logic here
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main() {
    InitADC();
    // Create a task for SPI communication
    xTaskCreate(pwm_task, "pwm_task", 2048 * 8, NULL, 5, NULL);

    // xTaskCreate(spi_task, "spi_task", 2048 * 8 , NULL, 5, NULL);
}
