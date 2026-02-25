#include "raster.h"
#include <osbind.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define SCREEN_BYTES_PER_ROW 80
#define LONGS_PER_SCREEN 8000

int main()
{
    UINT8 *base = (UINT8 *)Physbase();

    clear_screen((UINT32 *)base);
    plot_bitmap_8(base, 20, 20, 8, smiley_bitmap);
    plot_bitmap_8(base, 141, 636, 8, smiley_bitmap); /* right clipped */
    plot_bitmap_8(base, -5, 10, 8, smiley_bitmap);   /* top clipped */
    plot_bitmap_8(base, 10, -3, 8, smiley_bitmap);   /* left clipped */

    Cnecin();
    return 0;
}

void clear_screen(UINT32 *base)
{
    UINT32 *loc;
    int i = 0;
    loc = base;
    while (i++ < LONGS_PER_SCREEN)
    {
        *(loc++) = 0;
    }
}

/* returns visible width in pixels (0..sprite_width) and updates row/col/height + skip_x/skip_y */
UINT16 clip_left_top_right_bottom(INT16 *row, INT16 *col, UINT16 *height,
                                  UINT16 sprite_width, UINT16 *skip_x, UINT16 *skip_y)
{
    INT32 r = (INT32)(*row);
    INT32 c = (INT32)(*col);

    *skip_x = 0;
    *skip_y = 0;

    /* ---- top clip ---- */
    if (r < 0)
    {
        UINT16 s = (UINT16)(-r);
        if (s >= *height)
            return 0;
        *skip_y = s;
        *height = (UINT16)(*height - s);
        r = 0;
    }

    /* ---- bottom clip ---- */
    if (r >= SCREEN_HEIGHT)
        return 0;

    if ((UINT32)r + (UINT32)(*height) > (UINT32)SCREEN_HEIGHT)
        *height = (UINT16)(SCREEN_HEIGHT - (UINT16)r);

    /* ---- left clip ---- */
    if (c < 0)
    {
        UINT16 s = (UINT16)(-c);
        if (s >= sprite_width)
            return 0;
        *skip_x = s;
        c = 0;
    }

    /* ---- right clip ---- */
    if (c >= SCREEN_WIDTH)
        return 0;

    /* visible width = min(screen remaining, sprite remaining after skip_x) */
    {
        UINT16 visible = (UINT16)(SCREEN_WIDTH - (UINT16)c);
        UINT16 remaining = (UINT16)(sprite_width - *skip_x);

        if (visible > remaining)
            visible = remaining;

        *row = (INT16)r;
        *col = (INT16)c;
        return visible;
    }
}

void plot_bitmap_8(UINT8 *base, INT16 row, INT16 col, UINT16 height, const UINT8 *bitmap_8)
{
    UINT16 r, byte_col, bit_shift, visible, skip_x, skip_y;
    UINT32 offset;
    UINT8 *dest;
    UINT8 src, mask;

    visible = clip_left_top_right_bottom(&row, &col, &height, 8, &skip_x, &skip_y);
    if (visible == 0)
        return;

    bitmap_8 += skip_y;  /*skip rows clipped off the top*/
    byte_col = col >> 3; /*starting byte in row*/
    bit_shift = col & 7; /*bit offset inside that byte*/

    for (r = 0; r < height; r++)
    {
        offset = (UINT32)(row + (INT16)r) * (UINT32)SCREEN_BYTES_PER_ROW + (UINT32)byte_col;
        dest = base + offset;
        src = bitmap_8[r];
        /*left clip: drop leftmost pixels*/
        if (skip_x != 0)
        {
            src = (UINT8)(src << skip_x);
        }
        /* right clip: keep only leftmost 'visible' bits */
        if (visible < (UINT16)(8 - skip_x))
        {
            mask = (UINT8)(0xFF << (8 - visible));
            src = (UINT8)(src & mask);
        }

        if (bit_shift == 0)
        {
            *dest = (UINT8)(*dest | src);
        }
        else
        {
            UINT16 spill = 8 - bit_shift;
            /*first byte always gets the right-shifted portion*/
            *dest = (UINT8)(*dest | (UINT8)(src >> bit_shift));

            /*second byte ONLY if some visible pixels actually spill into it*/
            if (visible > spill && (byte_col + 1 < SCREEN_BYTES_PER_ROW))
            {
                dest[1] = (UINT8)(dest[1] | (UINT8)(src << spill));
            }
        }
    }
}
