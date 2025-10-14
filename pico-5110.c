#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "lcd-5110.h"

int main() {

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_init(RST);	
    gpio_init(CE);	
    gpio_init(DC);	
    gpio_init(DIN);	
    gpio_init(CLK);	
    gpio_init(BL);	
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_set_dir(RST, GPIO_OUT);
    gpio_set_dir(CE, GPIO_OUT);
    gpio_set_dir(DC, GPIO_OUT);	
    gpio_set_dir(DIN, GPIO_OUT);	
    gpio_set_dir(CLK, GPIO_OUT);	
    gpio_set_dir(BL, GPIO_OUT);

    sleep_ms(1000);

    // init lcd
    init_lcd();
    init_buffer();

    // clear the display
    clear_buffer();
    update_display();

    // Enable UART so we can print status output
    stdio_init_all();

    int cont = 0;

    sleep_ms(1000);

    gpio_put(LED_PIN, 1);

    //print_string("Ola Mundo!!!", BASIC, 0, 0);

    uint8_t raio = 2;
    while(true) {
        sleep_ms(1000);
        draw_circle(42, 24, raio);
        update_display();
        raio = raio + 2;
        if (raio > 23) {
            raio = 2;
            clear_buffer();
            update_display();
        }
    }
    return 0;
}
