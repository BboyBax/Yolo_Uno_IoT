#include <Arduino.h>
#include "Led_Blinky.h"
#include "Temp_Hum_Sensor.h"
#include "neo_pixel.h"
#include "LCD.h"
#include "Semaphore.h"



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  i2cSemaphore = xSemaphoreCreateMutex();
  xTaskCreate(Led_Blinky, "Led_Blinky", 2048, NULL, 2, NULL);
  xTaskCreate(Temp_Hum_Sensor, "Temp_Hum_Sensor", 2048, NULL, 2, NULL);
  xTaskCreate(Display_Temp_Hum, "Display_Temp_Hum", 2048, NULL, 2, NULL);
  xTaskCreate(Neo_Pixel, "Neo_Pixel", 2048, NULL, 2, NULL);
}

void loop() {
  // Serial.println("Hello Custom Board");
  delay(1000);
}