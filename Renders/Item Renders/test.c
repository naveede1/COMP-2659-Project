#include <stdio.h>
#include <osbind.h>

#define SCREEN_BYTES_PER_ROW 80
#define SPRITE_HEIGHT 32
typedef unsigned char UINT8;
typedef unsigned int UINT16;
typedef unsigned long UINT32;

UINT32 testLBM[SPRITE_HEIGHT] = /* Temp */
{
0x00FC3F00,
0x01FE7F80,
0x017A5E80,
0x037BDEC0,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x037BDEC0,
0x017A5E80,
0x01FE7F80,
0x00FE3F00,
0x00FC3F00,
0x01FE7F80,
0x017A5E80,
0x037BDEC0,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x037BDEC0,
0x017A5E80,
0x01FE7F80,
0x00FE3F00,
};

UINT32 testRBM[SPRITE_HEIGHT] = /* Temp */
{
0xF0000000,
0xF8000000,
0XCC000000,
0x86000000,
0x63C00000,
0x27200000,
0x07200000,
0xC0700000,
0x063C0000,
0x773E0000,
0x223F8000,
0x767FC000,
0x70FBE000,
0x07F7E000,
0xFFCFE000,
0xF88FE000,
0xE0FFC000,
0xC5FF8000,
0xC3FF0000,
0xC5F80000,
0x20F80000,
0x1FFC0000,
0x03FE0000,
0x2BFF0000,
0x57FF8000,
0xFFFF8000,
0x01FF8000,
0x001F0000,
0x00FF0000,
0x009CC000,
0x00422000,
0x00FFF000,
};

int test16_BM[16] = /* Temp */
{
0x0780,
0x0FF8,
0x0F20,
0x1210,
0x1308,
0x3170,
0x0438,
0x0FC0,
0x1E60,
0x1C20,
0x1E10,
0x1F10,
0x1710,
0x1220,
0x1CE0,
0x1EF0,
};

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

int main () {

    UINT32 *base = Physbase();

    plot_bitmap_32(base, 60,200, 32, testLBM);
    

    return 0;

}
