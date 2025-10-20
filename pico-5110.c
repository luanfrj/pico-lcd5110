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

    sleep_ms(1000);

    gpio_put(LED_PIN, 1);

    draw_line(0,0,83,0);
    draw_line(0,0,0,47);
    draw_line(83,0,83,47);
    draw_line(0,47,83,47);

    print_string("Brasil", BASIC8, 3, 3);
    print_string("2025", BASIC8, 3, 13);
    print_string("LUAN", BASIC8, 3, 23);
    update_display();

    uint8_t cont;
    for (cont = 0; cont < 5; cont++) {
        draw_circle(8 + 10 * cont, 40, 5);
    }
    update_display();
    while(true) {

    }
    return 0;
}
