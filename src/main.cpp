#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"

#include "ADS131M0x.h"
#include "SPI.h"

#define SCK     GPIO_NUM_18
#define MISO    GPIO_NUM_19
#define MOSI    GPIO_NUM_23
#define SS      GPIO_NUM_5

// ADS131M02
#define ADC_MOSI    GPIO_NUM_13
#define ADC_MISO    GPIO_NUM_26
#define ADC_CLK     GPIO_NUM_14
#define ADC_DRDY    GPIO_NUM_39
#define ADC_CS      GPIO_NUM_25
#define ADC_RESET   GPIO_NUM_16


SPIClass SpiADC(HSPI_HOST);
ADS131M0x adc;

void adcInit()
{
    adc.setClockSpeed(200000);
    adc.reset(ADC_RESET);
    adc.begin(&SpiADC, ADC_CLK, ADC_MISO, ADC_MOSI, ADC_CS, ADC_DRDY);
    adc.setInputChannelSelection(0, INPUT_CHANNEL_MUX_AIN0P_AIN0N);
    adc.setChannelPGA(0, CHANNEL_PGA_1);
}

extern "C" void app_main(){
    vTaskDelay(5);
    printf("INIT\r\n");
    adcInit();
    printf("adcInit finished\r\n");

    while(1){
        if (adc.isDataReady())
        {
            int32_t Val = adc.readADC().ch0;
            // int32_t Val = adc.readfastCh0();
            printf("ADC-Val :%ld", Val);

            uint32_t valabs = abs(Val);
            uint32_t cnt = valabs / 50000;
            if (Val >= 0)
            {
                for (size_t i = 0; i < cnt; i++)
                {
                    printf("+");
                }
            }
            else
            {
                for (size_t i = 0; i < cnt; i++)
                {
                    printf("-");
                }
            }
            printf("\r\n");
        }
    }
}
