#include "neo_pixel.h"

void neo_pixel(void *pvParameters){

    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    // Set all pixels to off to start
    strip.clear();
    strip.show();

    while (1){
        strip.setPixelColor(0, strip.Color(255, 0, 0));
        strip.show();

        vTaskDelay(500);

        strip.setPixelColor(0, strip.Color(0, 255, 0));
        strip.show();

        vTaskDelay(500);

        strip.setPixelColor(0, strip.Color(0, 0, 255));
        strip.show();

        vTaskDelay(500);
    }
    
}