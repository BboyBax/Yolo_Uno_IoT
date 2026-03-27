#ifndef __SEMAPHORE__
#define __SEMAPHORE__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

extern SemaphoreHandle_t i2cSemaphore;
extern float temperature;
extern float humidity;

#endif 
