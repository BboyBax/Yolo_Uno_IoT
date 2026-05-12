// #include "LCD.h"

// LiquidCrystal_I2C lcd(33, 16, 2); // LCD address

// void Display_Temp_Hum(void *pvParameters){
//     lcd.begin();
//     lcd.backlight();

//     while (1){
//         if(xSemaphoreTake(i2cSemaphore, portMAX_DELAY)){ 
//             lcd.clear();
//             lcd.setCursor(0,0);
//                 lcd.print("Tem:"); 
//                 lcd.print(temperature); 
//                 lcd.print((char)223); 
//                 lcd.print("C");
//             lcd.setCursor(0,1);
//                 lcd.print("Hum:"); 
//                 lcd.print(humidity);
//                 lcd.print(" %");
//             xSemaphoreGive(i2cSemaphore);
//         }
//         vTaskDelay(500);
//     }
    
// }
