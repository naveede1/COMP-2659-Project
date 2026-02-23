#include "raster.h"
#include <osbind.h>
#include <linea.h>

#define SCREEN_BYTES_PER_ROW 80
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define LONGS_PER_SCREEN 8000

void clear_screen(UINT32 *base)
{
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