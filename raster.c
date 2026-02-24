#include "raster.h"
#include <osbind.h>
#include <linea.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define SCREEN_BYTES_PER_ROW 80
#define LONGS_PER_SCREEN 8000

void clear_screen(UINT32 *base) {
    int i;
    UINT32 *loc;
    i = 0;
    loc = base;
    while (i++ < LONGS_PER_SCREEN)
        *(loc++) = 0;
}

void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width) {
    UINT8 *base8 = (UINT8 *)base;

    UINT16 r;
    UINT16 start_byte = col >> 3;
    UINT16 end_byte = (col + width - 1) >> 3;

    UINT8 start_bit = col & 7;
    UINT8 end_bit = (col + width - 1) & 7;

    for (r = row; r < (row + length); r++) {
        UINT8 *line = base8 + (UINT32)r * SCREEN_BYTES_PER_ROW;
        /* r to UINT32 to prevent 16-bit overflow when computing byte offset */
        UINT8 *start = line + start_byte;
        UINT8 *end = line + end_byte;

        UINT8 *curr = start;

        while (curr <= end) {
            UINT8 mask;

            if ((curr == start) && (curr == end)) {
                /*clear bits start_bit to end_bit*/
                UINT8 left = 0xFF >> start_bit;
                UINT8 right = 0xFF << (7 - end_bit);
                mask = left & right;
                *curr &= ~mask;
            } else if (curr == start) {
                /* clear from start_bit*/
                mask = 0xFF >> start_bit;
                *curr &= ~mask;
            } else if (curr == end) {
                /* clear from left edge of this byte up to end_bit */
                mask = 0xFF << (7 - end_bit);
                *curr &= ~mask;
            } else {
                *curr = 0x00;
            }
            curr++;
        }
    }
}

void plot_pixel(UINT8 *base, UINT16 row, UINT16 col) {
    if (row >= 0 && row < SCREEN_WIDTH && col >= 0 && col < SCREEN_HEIGHT){
        *(base + col * 80 + (row >> 3)) |= 1 << (7 - (row & 7));
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
    UINT8 *byte_base = (UINT8 *)base;
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

void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width) {
    UINT16 right_vertical_line_row = row + width - 1;    
    UINT16 bottom_horizontal_line_col = col + length - 1;
                                                  
    plot_horizontal_line(base, row, col, width);
    plot_horizontal_line(base, row, bottom_horizontal_line_col, width);
    plot_vertical_line(base, row, col, length);
    plot_vertical_line(base, right_vertical_line_row, col, length);
}

void plot_square(UINT32 *base, UINT16 row, UINT16 col, UINT16 side) {
    UINT16 right_vertical_line_row = row + side - 1;    
    UINT16 bottom_horizontal_line_col = col + side - 1;

    plot_horizontal_line(base, row, col, side);
    plot_horizontal_line(base, row, bottom_horizontal_line_col, side);
    plot_vertical_line(base, row, col, side);
    plot_vertical_line(base, right_vertical_line_row, col, side);
}

void plot_triangle(UINT32 *baseptr, UINT16 row, UINT16 col, UINT16 base, UINT16 height, UINT8 direction) {
    UINT16 diag_start_row, diag_start_col;
    UINT16 diag_end_row, diag_end_col;
    
    if (direction == 0) {
        plot_vertical_line(baseptr, row, col, height);
        plot_horizontal_line(baseptr, row, col, base);
        
        diag_start_row = row + base - 1;
        diag_start_col = col;
        diag_end_row = row;
        diag_end_col = col + height - 1;
        plot_line(baseptr, diag_start_row, diag_start_col, diag_end_row, diag_end_col);
        
    } else if (direction == 1) {
        plot_vertical_line(baseptr, row, col, height);
        plot_horizontal_line(baseptr, row - base + 1, col, base);
        
        diag_start_row = row - base + 1;
        diag_start_col = col;
        diag_end_row = row;
        diag_end_col = col + height - 1;
        plot_line(baseptr, diag_start_row, diag_start_col, diag_end_row, diag_end_col);
        
    } else if (direction == 2) {
        plot_vertical_line(baseptr, row, col - height + 1, height);
        plot_horizontal_line(baseptr, row, col, base);

        diag_start_row = row + base - 1;
        diag_start_col = col;
        diag_end_row = row;
        diag_end_col = col - height + 1;
        plot_line(baseptr, diag_start_row, diag_start_col, diag_end_row, diag_end_col);
        
    } else if (direction == 3) {
        plot_vertical_line(baseptr, row, col - height + 1, height);
        plot_horizontal_line(baseptr, row - base + 1, col, base);
        
        diag_start_row = row - base + 1;
        diag_start_col = col;
        diag_end_row = row;
        diag_end_col = col - height + 1;
        plot_line(baseptr, diag_start_row, diag_start_col, diag_end_row, diag_end_col);
    }
}