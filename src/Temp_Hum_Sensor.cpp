#include <Temp_Hum_Sensor.h>
#include "LiquidCrystal_I2C.h"
DHT20 dht20;

LiquidCrystal_I2C lcd(33, 16, 2); // địa chỉ LCD

void Temp_Hum_Sensor(void *pvParameters){

    Wire.begin(11,12);
    Serial.begin(115200);
    dht20.begin();
    lcd.init();
    lcd.backlight();

    while (1){
        dht20.read();
        float temperature = dht20.getTemperature();
        float humidity = dht20.getHumidity();

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
        lcd.clear();
        lcd.setCursor(0,0);
            lcd.print("Tem:"); 
            lcd.print(temperature); 
            lcd.print((char)223); 
            lcd.print("C");
        lcd.setCursor(0,1);
            lcd.print("Hum:"); 
            lcd.print(humidity);
            lcd.print(" %");
        delay(2000);

        vTaskDelay(5000);
    }
    
}