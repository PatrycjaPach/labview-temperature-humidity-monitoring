#include <cstdio>
#include "dht11.hpp" 

extern "C" {
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_log.h"
}


extern "C" void app_main(void)
{
    // 1️⃣ Utworzenie obiektu czujnika
    DHT11 dht(GPIO_NUM_26);

    // 2️⃣ Inicjalizacja UART (jeśli masz ją w klasie)
    dht.uart_init();

    ESP_LOGI("MAIN", "DHT11 init OK");

    while(1){
        if(dht.read() && dht.checksum()){
            dht.send_dht_uart();
        } else {
            ESP_LOGW("MAIN", "DHT11 read error");
        }

        vTaskDelay(pdMS_TO_TICKS(2000)); // DHT11 max ~1Hz
    }
}
