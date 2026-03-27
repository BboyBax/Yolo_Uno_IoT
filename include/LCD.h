#ifndef __LCD__
#define __LCD__

#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "Semaphore.h"

void Display_Temp_Hum(void *pvParameters);

#endif 