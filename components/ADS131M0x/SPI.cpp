/* 
 SPI.cpp - SPI library for esp8266

 Copyright (c) 2015 Hristo Gochkov. All rights reserved.
 This file is part of the esp8266 core for Arduino environment.
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdio.h>
#include "SPI.h"

static spi_device_handle_t spi_device;
static spi_device_interface_config_t dev_config;
static spi_bus_config_t bus_config;

SPIClass::SPIClass(spi_host_device_t spi_bus)
    :_spi_num(spi_bus)
    ,_use_hw_ss(false)
    ,_sck(0)
    ,_miso(0)
    ,_mosi(0)
    ,_ss(0)
    ,_div(0)
    ,_freq(1000000)
    ,_inTransaction(false)
{}

SPIClass::~SPIClass()
{
    end();
}

void SPIClass::begin(int8_t sck, int8_t miso, int8_t mosi, int8_t ss)
{
    _sck = sck;
    _miso = miso;
    _mosi = mosi;
    _ss = ss;

    printf("SCK: %d MISO: %d MOSI: %d SS: %d\r\n", _sck, _miso, _mosi, _ss);

    esp_err_t ret;

    // Configure the SPI bus parameters
    bus_config.mosi_io_num = _mosi;
    bus_config.miso_io_num = _miso;
    bus_config.sclk_io_num = _sck;
    bus_config.quadwp_io_num = -1;
    bus_config.quadhd_io_num = -1;
    bus_config.max_transfer_sz = 0;

    ret = spi_bus_initialize(_spi_num, &bus_config, 1);
    ESP_ERROR_CHECK(ret);
}

void SPIClass::end()
{
    spi_device_release_bus(spi_device);
}

void SPIClass::setHwCs(bool use)
{
    _use_hw_ss = use;
}

void SPIClass::setFrequency(uint32_t freq)
{

}

void SPIClass::setClockDivider(uint32_t clockDiv)
{

}

void SPIClass::setDataMode(uint8_t dataMode)
{

}

void SPIClass::setBitOrder(uint8_t bitOrder)
{
    
}

void SPIClass::beginTransaction(SPISettings settings)
{
    esp_err_t ret;

    // Configure the SPI device parameters

    dev_config.mode = settings._dataMode;
    dev_config.clock_speed_hz = settings._clock;
    dev_config.spics_io_num = (_use_hw_ss ? _ss : -1);
    dev_config.flags = SPI_DEVICE_NO_DUMMY;
    dev_config.queue_size = 1;
    dev_config.pre_cb = NULL;
    dev_config.post_cb = NULL;

    ret = spi_bus_add_device(_spi_num, &dev_config, &spi_device);
    ESP_ERROR_CHECK(ret);
}

void SPIClass::endTransaction()
{
    
}

void SPIClass::write(uint8_t data)
{
    esp_err_t ret;

    spi_transaction_t spi_transaction = {
        .flags = 0,
        .cmd = 0,
        .addr = 0,
        .length = 8,
        .rxlength = 0,
        .user = NULL,
        .tx_buffer = &data,
        .rx_buffer = NULL,
    };

    ret = spi_device_queue_trans(spi_device, &spi_transaction, portMAX_DELAY);
    ESP_ERROR_CHECK(ret);

    spi_transaction_t *trans;
    ret = spi_device_get_trans_result(spi_device, &trans, portMAX_DELAY);
    ESP_ERROR_CHECK(ret);
}

uint8_t SPIClass::transfer(uint8_t data)
{
    esp_err_t ret;
    uint8_t rx_data = 0;

    spi_transaction_t spi_transaction = {
        .flags = 0,
        .cmd = 0,
        .addr = 0,
        .length = 8,
        .rxlength = 8,
        .user = NULL,
        .tx_buffer = &data,
        .rx_buffer = &rx_data,
    };

    ret = spi_device_queue_trans(spi_device, &spi_transaction, portMAX_DELAY);
    ESP_ERROR_CHECK(ret);

    spi_transaction_t *trans;
    ret = spi_device_get_trans_result(spi_device, &trans, portMAX_DELAY);
    ESP_ERROR_CHECK(ret);

    return rx_data;
}

void SPIClass::write16(uint16_t data)
{
    esp_err_t ret;

    spi_transaction_t spi_transaction = {
        .flags = 0,
        .cmd = 0,
        .addr = 0,
        .length = 16,
        .rxlength = 0,
        .user = NULL,
        .tx_buffer = &data,
        .rx_buffer = NULL,
    };

    ret = spi_device_queue_trans(spi_device, &spi_transaction, portMAX_DELAY);
    ESP_ERROR_CHECK(ret);

    spi_transaction_t *trans;
    ret = spi_device_get_trans_result(spi_device, &trans, portMAX_DELAY);
    ESP_ERROR_CHECK(ret);
}

uint16_t SPIClass::transfer16(uint16_t data)
{
    esp_err_t ret;
    uint16_t rx_data = 0;

    spi_transaction_t spi_transaction = {
        .flags = 0,
        .cmd = 0,
        .addr = 0,
        .length = 16,
        .rxlength = 16,
        .user = NULL,
        .tx_buffer = &data,
        .rx_buffer = &rx_data,
    };

    ret = spi_device_queue_trans(spi_device, &spi_transaction, portMAX_DELAY);
    ESP_ERROR_CHECK(ret);

    spi_transaction_t *trans;
    ret = spi_device_get_trans_result(spi_device, &trans, portMAX_DELAY);
    ESP_ERROR_CHECK(ret);

    return rx_data;
}

void SPIClass::write32(uint32_t data)
{
    esp_err_t ret;

    spi_transaction_t spi_transaction = {
        .flags = 0,
        .cmd = 0,
        .addr = 0,
        .length = 32,
        .rxlength = 0,
        .user = NULL,
        .tx_buffer = &data,
        .rx_buffer = NULL,
    };

    ret = spi_device_queue_trans(spi_device, &spi_transaction, portMAX_DELAY);
    ESP_ERROR_CHECK(ret);

    spi_transaction_t *trans;
    ret = spi_device_get_trans_result(spi_device, &trans, portMAX_DELAY);
    ESP_ERROR_CHECK(ret);
}

uint32_t SPIClass::transfer32(uint32_t data)
{
    esp_err_t ret;
    uint32_t rx_data = 0;

    spi_transaction_t spi_transaction = {
        .flags = 0,
        .cmd = 0,
        .addr = 0,
        .length = 32,
        .rxlength = 32,
        .user = NULL,
        .tx_buffer = &data,
        .rx_buffer = &rx_data,
    };

    ret = spi_device_queue_trans(spi_device, &spi_transaction, portMAX_DELAY);
    ESP_ERROR_CHECK(ret);

    spi_transaction_t *trans;
    ret = spi_device_get_trans_result(spi_device, &trans, portMAX_DELAY);
    ESP_ERROR_CHECK(ret);

    return rx_data;
}

SPIClass SPI(VSPI_HOST);


