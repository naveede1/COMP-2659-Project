#include "raster.h"

#define SCREEN_BYTES_PER_ROW 80

void plot_bitmap_8(UINT8 *base, UINT16 row, UINT16 col, UINT16 height)
{
    static const UINT8 bitmap[8] = {
        /*Smilly sprite*/
        0x3C,
        0x42,
        0xA5,
        0x81,
        0xA5,
        0x99,
        0x42,
        0x3C};

    UINT16 byte_col = col >> 3; /* byte offset */
    UINT16 bit_shift = col & 7; /* sub-byte */
    UINT16 r;

    for (r = 0; r < height; r++)
    {
        UINT32 offset = (row + r) * SCREEN_BYTES_PER_ROW + byte_col;
        UINT8 *dest = base + offset;
        UINT8 src = bitmap[r & 7]; /* wrap if height > 8*/

        if (bit_shift == 0)
        {
            *dest |= src;
        }
        else
        {
            *dest |= (src >> bit_shift);
            *(dest + 1) |= (src << (8 - bit_shift));
        }
    }
}
