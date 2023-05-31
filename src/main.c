#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include "ads131m0x.h"
// #include "hal.h"
#include "rom/gpio.h"
#include "driver/ledc.h"
#include "driver/spi_master.h"

// Example pin, change as per your setup
#define MOSI_PIN    23
#define MISO_PIN    19
#define SCLK_PIN    18
#define CS_PIN      5
#define PWM_PIN     21

#define SPI_BUFF_SIZE   1

spi_device_handle_t spi;

void init_peripherals(void) {
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

    // Configure SPI settings
    spi_bus_config_t bus_cfg = {
        .miso_io_num = MISO_PIN,
        .mosi_io_num = MOSI_PIN,
        .sclk_io_num = SCLK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };
    spi_bus_initialize(VSPI_HOST, &bus_cfg, 0);

    spi_device_interface_config_t dev_cfg = {
        .mode = 1,  // POL = 0; PHA = 1
        .spics_io_num = -1,
        .queue_size = 1,
    };
    spi_bus_add_device(VSPI_HOST, &dev_cfg, &spi);

    // Set CS pin as output
    gpio_pad_select_gpio(CS_PIN);
    gpio_set_direction(CS_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(CS_PIN, 1);
}

uint32_t ads131m0x_send_frame(uint32_t data){
    uint32_t tx_data[SPI_BUFF_SIZE] = {0};
    uint32_t rx_data[SPI_BUFF_SIZE] = {0};
    tx_data[0] = data;
    spi_transaction_t spi_trans = {
        .length = 24,
        .tx_buffer = tx_data,
        .rx_buffer = rx_data
    };
    gpio_set_level(CS_PIN, 0);
    esp_rom_delay_us(1);
    spi_device_transmit(spi, &spi_trans);
    esp_rom_delay_us(1);
    gpio_set_level(CS_PIN, 1);
    printf("\ttx = %lX\trx = %lX\r\n", tx_data[0], rx_data[0]);

    return rx_data[0];
}

void app_main() {
    init_peripherals();

    while(1){
        ads131m0x_send_frame(0x0220);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
