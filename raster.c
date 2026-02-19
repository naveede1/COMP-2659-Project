#include "raster.h"
#include <osbind.h>

#define SCREEN_BYTES_PER_ROW 80

int main()
{
    UINT8 *base = Physbase();
    plot_bitmap_8(base, 100, 40, 8);
    plot_bitmap_16((UINT16 *)base, 100, 80, 16);
    plot_bitmap_32((UINT32 *)base, 100, 120, 32);
    return 0;
}

void plot_bitmap_8(UINT8 *base, UINT16 row, UINT16 col, UINT16 height)
{
    /*Smilly face*/
    static const UINT8 bitmap[8] = {
        0x3C,
        0x42,
        0xA5,
        0x81,
        0xA5,
        0x99,
        0x42,
        0x3C};

    UINT16 byte_col = col >> 3; /*byte offset*/
    UINT16 bit_shift = col & 7; /*sub-byte*/
    UINT16 r;
    for (r = 0; r < height; r++)
    {
        /*Compute offset framebuffer: (row+r) * bytes_per_row + column_byte*/
        UINT32 offset = (row + r) * SCREEN_BYTES_PER_ROW /*divide by 1 byte*/ + byte_col;
        UINT8 *dest = base + offset;
        UINT8 src = bitmap[r & 7]; /*wrapping when height > 8*/

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

void plot_bitmap_16(UINT16 *base, UINT16 row, UINT16 col, UINT16 height)
{
    /*from tutorial*/
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

    UINT16 word_col = col >> 4; /*word offset*/
    UINT16 bit_shift = col & 15;
    UINT16 r;
    for (r = 0; r < height; r++)
    {
        /*offset in 16-bits*/
        UINT32 offset = (row + r) * (SCREEN_BYTES_PER_ROW / 2) + word_col;
        UINT16 *dest = base + offset;
        /*wraps index with mask*/
        UINT16 src = invader_bitmap[r & (INVADER_HEIGHT - 1)]; /*wrap if height > INVADER_HEIGHT*/

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

void plot_bitmap_32(UINT32 *base, UINT16 row, UINT16 col, UINT16 height)
{
    static const UINT32 bitmap[BLOCK_HEIGHT] = {
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};

    UINT8 *base8 = (UINT8 *)base;
    UINT16 byte_col = col >> 3; /*computing the byte offset within a row*/
    UINT16 bit_shift = col & 7; /*computing the bit shift within a byte*/
    UINT16 r;
    for (r = 0; r < height; r++)
    {
        /* Destination pointer into framebuffer for this row*/
        UINT8 *dest = base8 + (UINT32)(row + r) * SCREEN_BYTES_PER_ROW + byte_col;
        UINT32 src = bitmap[r & 31]; /*wrapping at 32 bits*/

        UINT8 b0 = (src >> 24);
        UINT8 b1 = (src >> 16);
        UINT8 b2 = (src >> 8);
        UINT8 b3 = src;

        /* If byte-alligned, OR each source byte into consecutive destination bytes*/
        if (bit_shift == 0)
        {
            dest[0] |= b0;
            dest[1] |= b1;
            dest[2] |= b2;
            dest[3] |= b3;
        }
        else
        {
            /* else shift bytes across byte boundaries according to bit_shift*/
            dest[0] |= (b0 >> bit_shift);
            dest[1] |= (b0 << (8 - bit_shift)) | (b1 >> bit_shift);
            dest[2] |= (b1 << (8 - bit_shift)) | (b2 >> bit_shift);
            dest[3] |= (b2 << (8 - bit_shift)) | (b3 >> bit_shift);
            dest[4] |= (b3 << (8 - bit_shift));
        }
    }
}
