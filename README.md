


# ADS131M02 and ADS131M04 ESP IDF Library

ESP IDF lib for the  ADS131M02 and ADS131M04 24-bit Analog to Digital Converter.

Mostly based on the work of https://github.com/LucasEtchezuri/Arduino-ADS131M04
## Changes to original lib
* adaption for ADS131M02 and conditional code parts for ADS131M02 and ADS131M04
* modified interface for flexible SPI-Port
* method to change SPI clock 
* minor changes for speed optimation
* additonal interface description

Please notice: all modifications are only tested with ESP32, ESP32-S2, ESP32-S3 and ESP32-C3

## Helpfull Links
Datasheet = https://www.ti.com/product/ADS131M02

Datasheet = https://www.ti.com/product/ADS131M04

## Download and Installation


### Platform IO
Add in 'platform.ini' (no need to download before)
```
lib_deps =
  https://github.com/liwing1/ADS131M0x
``` 


