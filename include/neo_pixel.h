#ifndef __NEO_PIXEL__
#define __NEO_PIXEL__
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "global.h"

#define NEO_PIN 45
#define LED_COUNT 1
#define COLD            0
#define COOL            1
#define WARM            2
#define HOT             3
#define SCORCHING       4

extern int pre_state;
extern int temp_state;

void Neo_Pixel(void *pvParameters);

#endif