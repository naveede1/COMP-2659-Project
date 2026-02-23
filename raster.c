#include "raster.h"
#include <osbind.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

void plot_pixel(UINT8 *base, UINT16 row, UINT16 col) {
    UINT8 *byte_base = (UINT8 *)base;

    if (row >= 0 && row < SCREEN_WIDTH && col >= 0 && col < SCREEN_HEIGHT){
        *(byte_base + col * 80 + (row >> 3)) |= 1 << (7 - (row & 7));
    }
}

void plot_horizontal_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length) {
    UINT8 *byte_base = (UINT8 *)base;
    UINT8 *start_byte_loc = byte_base + col * 80 + (row >> 3);
    UINT8 *end_byte_loc = byte_base + col * 80 + ((row + length - 1) >> 3);

    UINT8 start_bit_location = col & 7;
    UINT8 end_bit_location = (col + length - 1) & 7;

    UINT8 *curr = start_byte_loc;

    while (curr <= end_byte_loc) {
        UINT8 mask;
        UINT8 number_bits;

        if ((curr == start_byte_loc) && (curr == end_byte_loc)) {
            number_bits = start_bit_location - end_bit_location + 1;
            mask = (1 << number_bits) - 1;
            mask = mask << end_bit_location;
            *curr |= mask; 
        } else if (curr == start_byte_loc) {
            number_bits = start_bit_location + 1;
            mask = (1 << number_bits) - 1;
            *curr |= mask; 
        } else if (curr == end_byte_loc) {
            number_bits = 7 - end_bit_location + 1;
            mask = (1 << number_bits) - 1;
            mask = mask << end_bit_location;
            *curr |= mask; 
        } else {
            mask = 0xFF;
            *curr |= mask;
        }
        curr++;
    }
}

void plot_vertical_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length) {
    UINT8 *byte_base = (UINT8 *)base; /* So we can work byte by byte */
    UINT16 i;
    UINT16 current_column;
    
    for (i = 0; i < length; i++) {
        current_column = col + i;
        *(byte_base + current_column * 80 + (row >> 3)) |= 1 << (7 - (row & 7));
    }
}

void plot_line(UINT32 *base, UINT16 start_row, UINT16 start_col, UINT16 end_row, UINT16 end_col) {
    UINT8 *byte_base = (UINT8 *)base;
    int abs_distance_x, abs_distance_y;
    int step_x, step_y;
    int error, temp_error;
    UINT16 current_row = start_row;
    UINT16 current_col = start_col;
    
    abs_distance_x = end_row > start_row ? end_row - start_row : start_row - end_row;
    abs_distance_y = end_col > start_col ? end_col - start_col : start_col - end_col;
    
    step_x = start_row < end_row ? 1 : -1;
    step_y = start_col < end_col ? 1 : -1;

    error = abs_distance_x - abs_distance_y;
    
    /* Bresenham's line algorithm */
    while (1) {
        *(byte_base + current_col * 80 + (current_row >> 3)) |= 1 << (7 - (current_row & 7));
        
        if (current_row == end_row && current_col == end_col) {
            break;
        }
        
        temp_error = 2 * error;
        
        if (temp_error > -abs_distance_y) {
            error -= abs_distance_y;
            current_row += step_x;
        }
        
        if (temp_error < abs_distance_x) {
            error += abs_distance_x;
            current_col += step_y;
        }
    }
}