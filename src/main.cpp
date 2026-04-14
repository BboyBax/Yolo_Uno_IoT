#include <Arduino.h>

void TaskLEDControl(void *pvParameters) {
  pinMode(GPIO_NUM_48, OUTPUT);
  int ledState = 0;
  while(1) {
    
    if (ledState == 0) {
      digitalWrite(GPIO_NUM_48, HIGH); 
    } else {
      digitalWrite(GPIO_NUM_48, LOW);
    }
    ledState = 1 - ledState;
    vTaskDelay(500);
  }
}


void setup() {
  Serial.begin(115200);
  xTaskCreate(TaskLEDControl, "LED Control", 2048, NULL, 2, NULL);
}

void loop() {
  delay(1000);
}