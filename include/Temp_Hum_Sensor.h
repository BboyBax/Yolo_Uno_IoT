#ifndef __TEMP_HUM_SENSOR__
#define __TEMP_HUM_SENSOR__
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "DHT20.h"
#include "LiquidCrystal_I2C.h"



void Temp_Hum_Sensor(void *pvParameters);

#endif