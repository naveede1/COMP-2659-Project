#include "raster.h"
#include <stdio.h>
#include <osbind.h>

#define BYTES_PER_SCREEN 32000 
#define SCREEN_WIDTH 640 
#define SCREEN_LENGTH 400

int main() {

    UINT16 r = 30;
    UINT16 c = 187;
    UINT16 l = 22;
    UINT16 w = 40;
    UINT32 *base = Physbase();

    /* clear_screen(base);*/

    clear_region(base, r, c, l, w);

    return 0;
}

void clear_screen(UINT32 *base) {

    int i = 0;
    UINT32 *loc = base;

    while (i++ < (BYTES_PER_SCREEN/2)) {
	    *(loc++) = 0;
    }
}

void clear_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width) {

    UINT32 *start_byte_loc = base + row * 80 + (col >> 3);
    UINT32 *end_byte_loc = base + row * 80 + ((col + length - 1) >> 3);

    UINT8 start_bit_location = row & 7;
    UINT8 end_bit_location = ((row + (length - 1)) & 7); 

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

void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width) {

    int i = row;

    for (i; i < width; i++) {

        UINT32 *start_byte_loc = base + i * 80 + (col >> 3);
        UINT32 *end_byte_loc = base + i * 80 + ((col + length - 1) >> 3);

        UINT8 start_bit_location = i & 7;
        UINT8 end_bit_location = ((i + (length - 1)) & 7); 

        UINT8 *curr = start_byte_loc;

        while (curr <= end_byte_loc) {
            UINT8 mask;
            UINT8 number_bits;

            if ((curr == start_byte_loc) && (curr == end_byte_loc)) {
                number_bits = start_bit_location - end_bit_location + 1;
                mask = (1 << number_bits) - 1;
                mask = mask << end_bit_location;
                *curr &= mask; 
            } else if (curr == start_byte_loc) {
                number_bits = start_bit_location + 1;
                mask = (1 << number_bits) - 1;
                *curr &= mask; 
            } else if (curr == end_byte_loc) {
                number_bits = 7 - end_bit_location + 1;
                mask = (1 << number_bits) - 1;
                mask = mask << end_bit_location;
                *curr &= mask; 
            } else {
                mask = 0x00;
                *curr &= mask;
            }
            curr++;
        }   
    }
}
