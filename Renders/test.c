#include <stdio.h>
#include <osbind.h>

#define SCREEN_BYTES_PER_ROW 80
#define SPRITE_HEIGHT 32
typedef unsigned char UINT8;
typedef unsigned int UINT16;
typedef unsigned long UINT32;

UINT32 testLBM[SPRITE_HEIGHT] =
{
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x0000007E,
0x000000FF,
0x000001E2,
0x000031A1,
0x000018C2,
0x00000F8C,
0x00003FC0,
0x00001EC8,
0x000029F8,
0x000001F0,
0x000000FF,
0x0000001E,
0x000003F8,
0x00000FFE,
0x000077FE,
0x000071FC,
0x00003C7C,
0x00001F1C,
0x00003FC4,
0x0000197C,
0x00000C74,
0x0000002E,
};


UINT32 testRBM[SPRITE_HEIGHT] = /* Temp */
{
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
};

int test_16_BM[16] = /* Temp */
{
0x0000,
0x0000,
0x0000,
0x0180,
0x0FF0,
0x1FF8,
0x1FF8,
0x1FF8,
0x1FF8,
0x1FF8,
0x0FF0,
0x0180,
0x0180,
0x0180,
0x0180,
0x0180,
};

int test2_16_BM[16] = /* Temp */
{
0x0F00,
0x08E0,
0x1880,
0x27B0,
0x2748,
0x7FF0,
0x0F60,
0x1F80,
0x1C80,
0x1C40,
0x1048,
0x2038,
0x4718,
0xD8F8,
0xE000,
0x7000,
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

    UINT16 *base = Physbase();

    
    /*plot_bitmap_32(base, 60,200, 32, testLBM);
    plot_bitmap_32(base, 60,232, 32, testRBM);*/
    
    plot_bitmap_16(base, 45, 198, 16, test_16_BM);
    plot_bitmap_16(base, 60, 200, 16, test2_16_BM);

    return 0;

}

/*
Remaining Bitmaps:
Mario - Jumping, Climbing, Hammer Up, Hammer Down
UI - Score, Lives, Bonus/Timer
Level - Girders, Ladder, Broken Ladder
*/


