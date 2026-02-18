#include "raster.h"
#include <osbind.h>

#define SCREEN_BYTES_PER_ROW 80

int main()
{
    UINT8 *base = Physbase();

    plot_bitmap_8(base, 16, 24, 8);
    plot_bitmap_16(base,32,64,16);
    return 0;
}
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
        UINT8 src = bitmap[r & 7]; /* wrap if height > 8     */

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
void plot_bitmap_16(UINT16 *base, UINT16 row, UINT16 col, UINT16 height)
{

#define INVADER_HEIGHT 16
    int invader_bitmap[INVADER_HEIGHT] =
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

    UINT16 word_col = col >> 4;  /* word offset */
    UINT16 bit_shift = col & 15; /* sub-word */
    UINT16 r;

    for (r = 0; r < height; r++)
    {
        UINT32 offset = (row + r) * (SCREEN_BYTES_PER_ROW / 2) + word_col;
        UINT16 *dest = base + offset;
        UINT16 src = invader_bitmap[r & (INVADER_HEIGHT - 1)]; /* wrap if height > INVADER_HEIGHT */

        if (bit_shift == 0)
        {
            *dest |= src;
        }
        else
        {
            *dest |= (src >> bit_shift);
            *(dest + 1) |= (src << (16 - bit_shift));
        }
    }
}
