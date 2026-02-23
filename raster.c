#include "raster.h"
#include <osbind.h>
#include <linea.h>

#define LONGS_PER_SCREEN 8000
#define SCREEN_BYTES_PER_ROW 80
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

void clear_screen(UINT32 *base)
{ /*From Aidan's*/
    int i;
    UINT32 *loc;
    i = 0;
    loc = base;
    while (i++ < LONGS_PER_SCREEN)
        *(loc++) = 0;
}

void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width)
{
    UINT8 *base8 = (UINT8 *)base;

    UINT16 r;
    UINT16 start_byte = col >> 3;
    UINT16 end_byte = (col + width - 1) >> 3;

    UINT8 start_bit = col & 7;
    UINT8 end_bit = (col + width - 1) & 7;

    for (r = row; r < (row + length); r++)
    {
        UINT8 *line = base8 + (UINT32)r * SCREEN_BYTES_PER_ROW;
        /* r to UINT32 to prevent 16-bit overflow when computing byte offset */
        UINT8 *start = line + start_byte;
        UINT8 *end = line + end_byte;

        UINT8 *curr = start;

        while (curr <= end)
        {
            UINT8 mask;

            if ((curr == start) && (curr == end))
            {
                /*clear bits start_bit to end_bit*/
                UINT8 left = 0xFF >> start_bit;
                UINT8 right = 0xFF << (7 - end_bit);
                mask = left & right;
                *curr &= ~mask;
            }
            else if (curr == start)
            {
                /* clear from start_bit*/
                mask = 0xFF >> start_bit;
                *curr &= ~mask;
            }
            else if (curr == end)
            {
                /* clear from left edge of this byte up to end_bit */
                mask = 0xFF << (7 - end_bit);
                *curr &= ~mask;
            }
            else
            {
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

void plot_bitmap_8(UINT8 *base, UINT16 row, UINT16 col, UINT16 height, const UINT8 *bitmap_8)
{
    UINT16 byte_col = col >> 3; /*byte offset*/
    UINT16 bit_shift = col & 7; /*sub-byte*/
    UINT16 r;
    for (r = 0; r < height; r++)
    {
        /*Compute offset framebuffer: (row+r) * bytes_per_row + column_byte*/
        UINT32 offset = (row + r) * SCREEN_BYTES_PER_ROW /*divide by 1 byte*/ + byte_col;
        UINT8 *dest = base + offset;
        UINT8 src = bitmap_8[r & 7]; /*wrapping when height > 8*/

        /* If column is byte-alligned, OR the source byte directly */
        if (bit_shift == 0)
        {
            *dest |= src;
        }
        else
        {
            /*elseshift source right into the current byte*/
            *dest |= (src >> bit_shift);
            /*And shift remaining bits into the next byte*/
            *(dest + 1) |= (src << (8 - bit_shift));
        }
    }
}

void plot_bitmap_16(UINT16 *base, UINT16 row, UINT16 col, UINT16 height, const UINT16 *bitmap_16)
{

    UINT16 word_col = col >> 4; /*word offset*/
    UINT16 bit_shift = col & 15;
    UINT16 r;
    for (r = 0; r < height; r++)
    {
        /*offset in 16-bits*/
        UINT32 offset = (row + r) * (SCREEN_BYTES_PER_ROW / 2) + word_col;
        UINT16 *dest = base + offset;
        /*wraps index with mask*/
        UINT16 src = bitmap_16[r & (15)]; /*wrap if height > INVADER_HEIGHT*/

        /*If alligned, OR the source directly*/
        if (bit_shift == 0)
        {
            *dest |= src;
        }
        else
        {
            /*else shift across word boundary*/
            *dest |= (src >> bit_shift);
            *(dest + 1) |= (src << (16 - bit_shift)); /*remaining to the next*/
        }
    }
}

void plot_bitmap_32(UINT32 *base, UINT16 row, UINT16 col, UINT16 height, const UINT32 *bitmap_32)
{
    UINT8 *base8 = (UINT8 *)base;
    UINT16 byte_col = col >> 3;
    UINT16 bit_shift = col & 7;
    UINT16 r;
    for (r = 0; r < height; r++)
    {
        UINT8 *dest = base8 + (UINT32)(row + r) * SCREEN_BYTES_PER_ROW + byte_col;
        UINT32 src = bitmap_32[r & 31];

        UINT8 b0 = (src >> 24);
        UINT8 b1 = (src >> 16);
        UINT8 b2 = (src >> 8);
        UINT8 b3 = src;

        if (bit_shift == 0)
        {
            dest[0] |= b0;
            dest[1] |= b1;
            dest[2] |= b2;
            dest[3] |= b3;
        }
        else
        {
            dest[0] |= (b0 >> bit_shift);
            dest[1] |= (b0 << (8 - bit_shift)) | (b1 >> bit_shift);
            dest[2] |= (b1 << (8 - bit_shift)) | (b2 >> bit_shift);
            dest[3] |= (b2 << (8 - bit_shift)) | (b3 >> bit_shift);
            dest[4] |= (b3 << (8 - bit_shift));
        }
    }
}

void plot_character(UINT8 *base, UINT16 row, UINT16 col, char c)
{
    UINT8 *font;
    UINT16 byte_col, bit_shift, r;
    UINT32 offset;
    UINT8 *dest;
    UINT8 src;
    /*Check if it is within the screen boundaries*/
    if (row >= SCREEN_HEIGHT || col >= SCREEN_WIDTH)
    {
        return;
    }
    font = (UINT8 *)V_FNT_AD; /*Get the start add. of font table*/
    byte_col = (UINT16)(col >> 3);
    bit_shift = (UINT16)(col & 7);
    for (r = 0; r < 16; r++)
    {
        if ((UINT16)(row + r) >= SCREEN_HEIGHT)
        {
            return;
        }
        /* row r of glyph c: font[c + 256 * r] ?//from lab*/
        src = font[(UINT16)(UINT8)c + (UINT16)(256 * r)];
        offset = (UINT32)(row + r) * SCREEN_BYTES_PER_ROW + byte_col;
        dest = base + offset;
        if (bit_shift == 0)
        {
            dest[0] |= src;
        }
        else
        {
            dest[0] |= (UINT8)(src >> bit_shift);
            if (byte_col < (SCREEN_BYTES_PER_ROW - 1))
            {
                dest[1] |= (UINT8)(src << (8 - bit_shift));
            }
        }
    }
}

void plot_string(UINT8 *base, UINT16 row, UINT16 col, char *str)
{
    while (*str)
    {
        plot_character(base, row, col, *str++);
        col += 8; /*Move to the next character position*/
    }
}