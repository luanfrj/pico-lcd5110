#include "lcd-5110.h"

// Buffer para armazenamento de informações da tela;
uint8_t* buffer;

void send_byte(unsigned char byte)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        gpio_put(CLK, 0);
        if (byte > 127) {
            gpio_put(DIN, 1);
        }
        else
        {
            gpio_put(DIN, 0);
        }

        sleep_us(1);
        // rise clock
        gpio_put(CLK, 1);

        // shift byte
        byte = byte << 1;
    }
    gpio_put(CLK, 0);
}

void send_data(unsigned char data)
{
    gpio_put(DC, 1);
    send_byte(data);
}

void send_command(unsigned char cmd)
{
    gpio_put(DC, 0);
    send_byte(cmd);
}

void init_lcd()
{
    gpio_put(RST, 1);
    gpio_put(CE, 1);
    gpio_put(DC, 1);
    gpio_put(DIN, 1);
    gpio_put(CLK, 1);
    gpio_put(BL, 1);

    gpio_put(RST, 1);
    gpio_put(CE, 1);
    gpio_put(DC, 1);
    gpio_put(DIN, 0);
    gpio_put(CLK, 0);
    gpio_put(BL, 0);

    sleep_ms(50);

    // reset the controller
    gpio_put(RST, 0);
    sleep_us(1);
    gpio_put(RST, 1);

    // start
    gpio_put(CE, 0);
    send_command(0x21);
    send_command(0x9E);    // set LCD Vop (contrast)
    send_command(0x20);    // LCD basic commands
    send_command(0x0C);

    // turn on backlight
    gpio_put(BL, 1);
}

void clear_buffer()
{
    uint16_t i;
    for(i = 0; i < 504; i++)
    {
        buffer[i] = 0;
    }
}

void update_display() {
    uint16_t i;
    set_cursor(0, 0);

    for(i = 0; i < 504; i++)
    {
        send_data(buffer[i]);
    }
}

void init_buffer() {
    buffer = (uint8_t*) malloc(504 * sizeof(uint8_t));
}

void set_cursor(unsigned char x, unsigned char y)
{
    unsigned char x_addr = 0x80 | x;
    unsigned char y_addr = 0x40 | y;
    send_command(0x20);
    send_command(x_addr);
    send_command(y_addr);
}

void write_pixel(uint8_t x, uint8_t y) {
    if (x < 0 || x > 83 || y < 0 || y > 47) {
        return;
    }

    uint8_t bank = y / 8;
    uint8_t data = buffer[x + bank * 84] | 1 << (y % 8);
    buffer[x + bank * 84] = data;
}

void draw_circle(uint8_t x0, uint8_t y0, uint8_t radius)
{
    uint8_t x = radius;
    uint8_t y = 0;
    int8_t err = 0;

    while (x >= y)
    {
        write_pixel(x0 + x, y0 + y);
        write_pixel(x0 + y, y0 + x);
        write_pixel(x0 - y, y0 + x);
        write_pixel(x0 - x, y0 + y);
        write_pixel(x0 - x, y0 - y);
        write_pixel(x0 - y, y0 - x);
        write_pixel(x0 + y, y0 - x);
        write_pixel(x0 + x, y0 - y);

        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}

void print_char_basic(char c, uint8_t x, uint8_t y)
{
    unsigned char i;
    
    for (i = 0; i < 5; i++)
    {
        set_cursor(x+i, y);
        send_data(FontBasic[c - 0x20][i]);
    }
    set_cursor(x+i, y);
    send_data(0x00);
}


void print_char_mega(char c, uint8_t x, uint8_t y)
{
    uint8_t i,j,sub_col, x_temp, y_temp;
    uint16_t col;

    x_temp = x;
    y_temp = y;

    for (j = 0; j < 4; j++) {
        set_cursor(x, y + j);
        for (i = 0; i < 16; i++)
        {
            if (c - 0x2E >= 0) {
                col = FontMega[c - 0x2E][i];
                send_data((uint8_t) (col >> (8 * j)));
            } else {
                send_data(0x00);
            }
        }
    }
    //send_data(0x00);
}

void print_string(char *str, font_t font, uint8_t x, uint8_t y)
{
    uint8_t i = 0;
    set_cursor(x, y);
    while(*str)
    {
        switch (font)
        {
            case BASIC:
                print_char_basic(*str, x + 5 * i, y);
                break;
            case MEGA:
                print_char_mega(*str, x + 16 * i, y);
                break;
            default:
                break;      
        }       
        str++;
        i++;
    }
}
