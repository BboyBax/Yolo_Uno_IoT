#include "led_blinky.h"

void led_blinky(void *pvParameters){
    SystemHandles* handles = (SystemHandles*)pvParameters;
    SensorData data;
    float currentTemp = 25.0f; // init with safe normal value

    pinMode(GPIO_NUM_48, OUTPUT); // Initialize LED pin
    int ledState = 0;
  
    while(1){
        // non-blocking peek from queue
        if(xQueuePeek(handles->qLed, &data, 0) == pdTRUE){
          // read success
          currentTemp = data.temperature;
        }
        if (ledState == 0) {
            digitalWrite(GPIO_NUM_48, HIGH); // Turn ON LED
        } else {
            digitalWrite(GPIO_NUM_48, LOW); // Turn OFF LED
        }
        ledState = 1 - ledState;
        vTaskDelay(500);
    }
}
