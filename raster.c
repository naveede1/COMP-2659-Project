#include "raster.h"
#include <osbind.h>
#include <linea.h>

#define SCREEN_BYTES_PER_ROW 80
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

int main()
{
    /*
    UINT8 *base = Physbase();
    plot_bitmap_8(base, 100, 40, 8, smiley_bitmap);
    plot_bitmap_16((UINT16 *)base, 100, 80, 16, invader_bitmap);
    plot_bitmap_32((UINT32 *)base, 100, 120, 32, block_bitmap);*/

    UINT16 r = 0;
    UINT16 c = 0;
    UINT16 l = 40;
    UINT16 w = 40;
    UINT32 *base = Physbase();
    clear_region(base, r, c, l, w);

    return 0;
}
void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width)
{
    UINT8 *base8 = (UINT8 *)base; /* cast to byte pointer for byte-level access */

    UINT16 r;
    UINT16 start_byte = col >> 3;             /*index of 1st byte in the row the region*/
    UINT16 end_byte = (col + width - 1) >> 3; /*last byte index in the row the region*/

    UINT8 start_bit = col & 7;             /*bit pos within the first byte where it starts*/
    UINT8 end_bit = (col + width - 1) & 7; /*bit pos within the last byte where it ends */

    for (r = row; r < row + length; r++)
    {
        UINT8 *line = base8 + (UINT32)r * SCREEN_BYTES_PER_ROW; /*pointer to the start of row r*/

        UINT8 *start = line + start_byte; /*pointer to the first byte of the region on this row*/
        UINT8 *end = line + end_byte;     /*pointer to the last byte of the region on this row */

        UINT8 *curr = start;

        while (curr <= end)
        {
            UINT8 mask;

            if ((curr == start) && (curr == end))
            {
                /* region fits within a single byte, mask only the bits between start_bit and end_bit */
                UINT8 left = 0xFF >> start_bit;      /*1s from start_bit to bit 0*/
                UINT8 right = 0xFF << (7 - end_bit); /*1s from bit 7 to end_bit*/
                mask = left & right;                 /*overlap gives us exactly what bits to clear*/
                *curr &= ~mask;
            }
            else if (curr == start)
            {
                /* first byte: clear only from start_bit to the end of the byte */
                mask = 0xFF >> start_bit;
                *curr &= ~mask;
            }
            else if (curr == end)
            {
                /* last byte: clear only from the start of the byte to end_bit */
                mask = 0xFF << (7 - end_bit);
                *curr &= ~mask;
            }
            else
            {
                /*Clearing all bits in middle*/
                *curr = 0x00;
            }

            curr++; /* move to the next byte */
        }
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
    UINT16 byte_col = col >> 3; /*computing the byte offset within a row*/
    UINT16 bit_shift = col & 7; /*computing the bit shift within a byte*/
    UINT16 r;
    for (r = 0; r < height; r++)
    {
        /* Destination pointer into framebuffer for this row*/
        UINT8 *dest = base8 + (UINT32)(row + r) * SCREEN_BYTES_PER_ROW + byte_col;
        UINT32 src = bitmap_32[r & 31]; /*wrapping at 32 bits*/

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

void clear_screen(UINT32 *base)
{ /*From Aidan's*/
    int i;
    UINT32 *loc;
    i = 0;
    loc = base;
    while (i++ < LONGS_PER_SCREEN)
        *(loc++) = 0;
}

void plot_pixel(UINT8 *base, UINT16 row, UINT16 col)
{ /*from Naveed's PR*/
    if (row >= 0 && row < SCREEN_WIDTH && col >= 0 && col < SCREEN_HEIGHT)
    {
        *(base + col * 80 + (row >> 3)) |= 1 << (7 - (row & 7));
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
