#ifndef DHT11_HPP
#define DHT11_HPP

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "rom/ets_sys.h"   // ets_delay_us

/*RAMKA DHT11
START OD ESP
0-musi podać mój ESP32 "Hej"
1-przez króki czas że skończył mówić hej

START OD DHT
1 0-wtedy wiemy że jest komunikacja

DANE
010-tak wygląda jedna dana
czy to jest 0 czy 1 to w zależności 
od tego jak długo jest stan wysoki  
tab[0]-hum liczba
tab[1]-wilgotność procent
tab[2]-temp licz
tab[3]-temp znak 
tab[4]-checksum
*/
class DHT11{
private:
    gpio_num_t _pin {GPIO_NUM_26};

public:
    int64_t now=esp_timer_get_time();
    bool result;
    uint8_t tab[5]; 

    DHT11(gpio_num_t pin):_pin(pin){
        gpio_reset_pin(pin);
        gpio_set_direction(pin, GPIO_MODE_OUTPUT);
        gpio_set_pull_mode(pin, GPIO_PULLUP_ONLY);
        gpio_set_level(_pin, 1);
    }

    bool wait_level(int lvl, int timeout_us){
        int64_t start=esp_timer_get_time();

        while(gpio_get_level(_pin)!=lvl){
            if(esp_timer_get_time()-start>timeout_us){
                return false;
            }
        }
        return true;
    }


    bool start(){
        int ok;
        for(int i=0; i<5;i++){
            tab[i]=0;
        }

        //low from esp
        gpio_set_direction(_pin, GPIO_MODE_OUTPUT);
        gpio_set_level(_pin, 0);
        ets_delay_us(18000);
        //high from esp
        gpio_set_level(_pin, 1); 
        ets_delay_us(30);
        //esp input
        gpio_set_direction(_pin, GPIO_MODE_INPUT);

        if(!wait_level(0, 200)) {
            return 0;
        }
        if(!wait_level(1,200)){
            return 0;
        }

        return 1;
    } //void start

    int read(){
        if(!start()){
            return 0;
        }
        int bajtCount=0;
        int bajtIndex=0;

        for(int i=0; i<40; i++){

            //start
            if(!wait_level(0, 200)){
                return 0;
            }

            //high
            if(!wait_level(1, 200)){
                return 0;
            }
            int64_t start_t=esp_timer_get_time();

            //high end
            if(!wait_level(0, 200)){
                return 0;
            }
            int64_t high_time=esp_timer_get_time()-start_t;
            int bit;

            if(high_time<50){
                bit=0;
            } else{
                bit=1;
            }
            uint8_t bajt;

            bajt<<=1;
            bajt|=bit;
            bajtCount++;

            if(bajtCount==8){
                tab[bajtIndex]=bajt;
                bajtIndex++;
                bajt=0;
                bajtCount=0;
            }
        } //for
    } //int read

    bool checksum(){
        uint8_t sum;
        if(sum!=tab[0]+tab[1]+tab[2]+tab[3]){
            return sum==tab[4];
        }
    }//bool chcksum

};//class

#endif