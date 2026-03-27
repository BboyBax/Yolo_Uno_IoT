#include "Led_Blinky.h"

void Led_Blinky(void *pvParameters) {
    pinMode(GPIO_NUM_48, OUTPUT); // Initialize LED pin
    int ledState = 0;
    while(1) {
        // if(xSemaphoreTake(i2cSemaphore, portMAX_DELAY)){
            if (ledState == 0) {
                digitalWrite(GPIO_NUM_48, HIGH); // Turn ON LED
            } else {
                digitalWrite(GPIO_NUM_48, LOW); // Turn OFF LED
            }
            ledState = 1 - ledState;
        // xSemaphoreGive(i2cSemaphore);
        // }
        vTaskDelay(500);
    }
}