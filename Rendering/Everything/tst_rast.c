#include "raster.h"
#include <unistd.h>
#include <osbind.h>
#include <linea.h>

void test_clear_screen(UINT32 *base);
void test_clear_region(UINT32 *base);
void plot_various_pixels(UINT8 *base);
void plot_border_pixels(UINT8 *base);
void plot_various_h_lines(UINT32 *base);
void plot_various_v_lines(UINT32 *base);
void test_rectangle(UINT32 *base);
void test_square(UINT32 *base);
void test_triangle(UINT32 *base);
void test_bitmap_8(UINT8 *base);
void test_bitmap_16(UINT16 *base);
void test_bitmap_32(UINT32 *base);
void test_plot_char(UINT8 *base);
void test_plot_string(UINT8 *base);

static const UINT8 smiley_bitmap[8] =
    {
        0x3C,
        0x42,
        0xA5,
        0x81,
        0xA5,
        0x99,
        0x42,
        0x3C,
};

static const UINT16 invader_bitmap[16] =
    {
        0x0000,
        0x0810,
        0x0810,
        0x0420,
        0x0240,
        0x1FF8,
        0x2004,
        0x4662,
        0x4002,
        0x43C2,
        0x2424,
        0x1008,
        0x0FF0,
        0x0240,
        0x0E70,
        0x0000,
};

static const UINT32 block_bitmap[32] =
    {
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
};

int main() {
    UINT8 *eight_base = Physbase();
    UINT16 *sixteen_base = Physbase();
    UINT32 *thirty_two_base = Physbase();

    clear_screen(thirty_two_base);
    test_plot_string(eight_base);

    return 0;
}

void test_clear_screen(UINT32 *base) {
    test_triangle(base);
    sleep(2);
    clear_screen(base);
}

void test_clear_region(UINT32 *base) {
    /* Seems to be missing to clear the first pixel? */
    plot_rectangle(base, 20, 20, 40, 40);
    sleep(2);
    clear_region(base, 20, 20, 80, 80); 
}


void plot_various_pixels(UINT8 *base) {
    plot_pixel(base, 50, 60);
    plot_pixel(base, 100, 100);
    plot_pixel(base, 120, 300);
}

void plot_border_pixels(UINT8 *base) {
    plot_pixel(base, 0, 0);      
    plot_pixel(base, 639, 0);    
    plot_pixel(base, 0, 398);
    plot_pixel(base, 639, 398);   
}

void plot_various_h_lines(UINT32 *base) {
    plot_horizontal_line(base, 3, 100, 50);
    plot_horizontal_line(base, 23, 170, 50);
    plot_horizontal_line(base, 0, 20, 50);
}

void plot_various_v_lines(UINT32 *base) {
    plot_vertical_line(base, 3, 100, 50);
    plot_vertical_line(base, 23, 170, 50);
    plot_vertical_line(base, 0, 20, 50); 
}

void test_rectangle(UINT32 *base) {
    plot_rectangle(base, 100, 150, 50 , 60);
}

void test_square(UINT32 *base) {
    plot_square(base, 100, 150, 50);
}

void test_triangle(UINT32 *base) {
    plot_triangle(base, 300, 100, 50, 40, 0);  
    plot_triangle(base, 400, 100, 50, 40, 1);  
    plot_triangle(base, 300, 200, 50, 40, 2);  
    plot_triangle(base, 400, 200, 50, 40, 3);
}

void test_bitmap_8(UINT8 *base) {
    plot_bitmap_8(base, 100, 40, 8, smiley_bitmap);
}

void test_bitmap_16(UINT16 *base) {
    plot_bitmap_16(base, 100, 80, 16, invader_bitmap);
}

void test_bitmap_32(UINT32 *base) {
    plot_bitmap_32(base, 100, 120, 32, block_bitmap);
}

void test_plot_char(UINT8 *base) {
    linea0();
    plot_character(base, 50, 50, 'a');
}

void test_plot_string(UINT8 *base) {
    linea0();
    plot_string(base, 0, 0, "Hello, world!");
}
