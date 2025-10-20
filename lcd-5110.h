#ifndef LCD_5110_H
#define LCD_5110_H

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/malloc.h"
#include "pico/binary_info.h"
#include "font-table.h"

#define RST	10
#define CE	11
#define DC	12
#define DIN	13
#define CLK	14
#define BL	15

typedef enum {BASIC, MEGA, BASIC8} font_t;

void init_lcd();

void init_buffer();

void clear_buffer();

void update_display();

void set_cursor(unsigned char x, unsigned char y);

void write_pixel(uint8_t x, uint8_t y, uint8_t value);

void draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

void draw_circle(uint8_t x0, uint8_t y0, uint8_t radius);

void print_string(char *str, font_t font, uint8_t x, uint8_t y);

#endif