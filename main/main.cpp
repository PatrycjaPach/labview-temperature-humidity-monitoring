#include <cstdio> 

extern "C" {
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_log.h"
}
//DHT11 mogę na 5v lub 3.3v i mogę na gpio26
extern "C" void app_main(void){

    while(1){
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}