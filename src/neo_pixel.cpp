#include "neo_pixel.h"

int pre_state = -1;
int temp_state = -1;

int get_temp_state(float temperature){
    if (temperature <= 20) return COLD;
    else if (temperature <= 25) return COOL;
    else if (temperature <= 30) return WARM;
    else if (temperature <= 35) return HOT;
    else return SCORCHING;
}

void display_cold(){
    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    strip.setBrightness(50);
    // Set all pixels to off to start
    strip.clear();
    strip.show();

    strip.setPixelColor(0, strip.Color(0, 255, 255));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(0, 255, 255));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
    vTaskDelay(500);
                
    strip.setPixelColor(0, strip.Color(0, 255, 255));
    strip.show();
    vTaskDelay(500);   
}

void display_cool(){
    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    strip.setBrightness(50);
    // Set all pixels to off to start
    strip.clear();
    strip.show();

    strip.setPixelColor(0, strip.Color(0, 255, 0));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(0, 255, 0));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
    vTaskDelay(500);
                
    strip.setPixelColor(0, strip.Color(0, 255, 0));
    strip.show();
    vTaskDelay(500);   
}

void display_warm(){
    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    strip.setBrightness(50);
    // Set all pixels to off to start
    strip.clear();
    strip.show();

    strip.setPixelColor(0, strip.Color(255, 255, 0));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(255, 255, 0));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
    vTaskDelay(500);
                
    strip.setPixelColor(0, strip.Color(255, 255, 0));
    strip.show();
    vTaskDelay(500);   
}

void display_hot(){
    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    strip.setBrightness(50);
    // Set all pixels to off to start
    strip.clear();
    strip.show();

    strip.setPixelColor(0, strip.Color(255, 100, 0));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
    vTaskDelay(500);
    strip.setPixelColor(0, strip.Color(255, 100, 0));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
    vTaskDelay(500);
                
    strip.setPixelColor(0, strip.Color(255, 100, 0));
    strip.show();
    vTaskDelay(500);   

    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
    vTaskDelay(500); 
}

void display_scorching(){
    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    strip.setBrightness(50);
    // Set all pixels to off to start
    strip.clear();
    strip.show();

    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.show();
    vTaskDelay(500);

    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
    vTaskDelay(500);
                
    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.show();
    vTaskDelay(500);   
}

void display_all_time(int state){
    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    strip.setBrightness(50);
    // Set all pixels to off to start
    strip.clear();
    strip.show();
    switch (state){
        case COLD:
            strip.setPixelColor(0, strip.Color(0, 255, 255));
            strip.show();
            break;
        case COOL:
            strip.setPixelColor(0, strip.Color(0, 255, 0));
            strip.show();
            break;         
        case WARM:
            strip.setPixelColor(0, strip.Color(255, 255, 0));
            strip.show();
            break;   
        case HOT:
            strip.setPixelColor(0, strip.Color(255, 100, 0));
            strip.show();
            break;
        case SCORCHING:
            strip.setPixelColor(0, strip.Color(255, 0, 0));
            strip.show();
            break;
        default:
            break;
    }
}


void Neo_Pixel(void *pvParameters){
    while (1){
        if(xSemaphoreTake(i2cSemaphore, portMAX_DELAY)){
            temp_state = get_temp_state(temperature);
            switch (temp_state){
            case COLD:
                if (temp_state != pre_state){
                    display_cold();
                    pre_state = temp_state;
                } else {
                    display_all_time(temp_state);
                }
                break;
            case COOL:
                if (temp_state != pre_state){
                    display_cool();
                    pre_state = temp_state;
                } else {
                    display_all_time(temp_state);
                }
                break;         
            case WARM:
                if (temp_state != pre_state){
                    display_warm();
                    pre_state = temp_state;
                } else {
                    display_all_time(temp_state);
                }
                break;   
            case HOT:
                if (temp_state != pre_state){
                    display_hot();
                    pre_state = temp_state;
                } else {
                    display_all_time(temp_state);
                }
                break;
            case SCORCHING:
                if (temp_state != pre_state){
                    display_scorching();
                    pre_state = temp_state;
                } else {
                    display_all_time(temp_state);
                }
                break;
            default:
                break;
            }
            xSemaphoreGive(i2cSemaphore);
        }
        vTaskDelay(500);
    }
    
}