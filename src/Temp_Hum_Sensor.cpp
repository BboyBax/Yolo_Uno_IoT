#include <Temp_Hum_Sensor.h>
DHT20 dht20;

void Temp_Hum_Sensor(void *pvParameters){

    Wire.begin(11,12);
    Serial.begin(115200);
    dht20.begin();

    while (1){
        if(xSemaphoreTake(i2cSemaphore, portMAX_DELAY)){ 
            dht20.read();
            temperature = dht20.getTemperature();
            humidity = dht20.getHumidity();

            if (isnan(temperature) || isnan(humidity)){
                Serial.println("Failed to read from DHT sensor."); 
               return;  
            }

            Serial.print("Temperature: ");
            Serial.print(temperature);
            Serial.write(176);
            Serial.println("C");
            Serial.print("Humidity: ");
            Serial.print(humidity);
            Serial.println("%");
            xSemaphoreGive(i2cSemaphore);
        }
        vTaskDelay(5000);
    }
    
}