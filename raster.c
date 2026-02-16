#include <raster.h>

#define INVADER_HEIGHT 8

int invader_bitmap[INVADER_HEIGHT] = {
    0x0000,
    0x0810,
    0x0810,
    0x0420,
    0x0240,
    0x1FF8,
    0x2004,
    0x4662,
};

void plot_bitmap_8(UINT8 *base, UINT16 row, UINT16 col, UINT16 height)
{
    for (int r = 0; r < height; r++)
    {
        UINT16 data = invader_bitmap[r];

        // loop 8 bits
        for (int b = 0; b < 8; b++)
        {
            if (data & (0x80 >> b)) // pixel ON
            {
                plot_pixel(base, row + r, col + b);
            }
        }
    }
}