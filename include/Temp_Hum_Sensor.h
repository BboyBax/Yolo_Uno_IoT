#ifndef __TEMP_HUM_SENSOR__
#define __TEMP_HUM_SENSOR__
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "DHT20.h"
#include "global.h"


void Temp_Hum_Sensor(void *pvParameters);
void Temp_Humi_LCD_Display(void *pvParameters);

#endif