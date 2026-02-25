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
    plot_bitmap_8(base, 20, 20, 8, smiley_bitmap);   /*full*/
    plot_bitmap_8(base, 141, 636, 8, smiley_bitmap); /*right*/
    plot_bitmap_8(base, -5, 10, 8, smiley_bitmap);   /*top*/
    plot_bitmap_8(base, 10, -3, 8, smiley_bitmap);   /*left*/
    plot_bitmap_8(base, 396, 20, 8, smiley_bitmap);  /*bottom*/
    Cnecin();
    return 0;
}

UINT16 clip_left_top_right_bottom(INT16 *row, INT16 *col, UINT16 *height,
                                  UINT16 sprite_width, UINT16 *x_skip, UINT16 *y_skip)
{
    INT16 r = *row;
    INT16 c = *col;

    *x_skip = 0;
    *y_skip = 0;

    /* ---- top clip ---- */
    /*If starts above, skipp the off-screen rows and decrease the height*/
    if (r < 0)
    {
        UINT16 s = -r;
        /*if height is small then draw nothing*/
        if (s >= *height)
        {
            return 0;
        }
        *y_skip = s;
        *height -= s;
        r = 0;
    }

    /* ---- bottom clip ---- */
    /*same logic as top clip but just camparing with the height*/
    if (r >= SCREEN_HEIGHT)
    {
        return 0;
    }
    if (r + *height > SCREEN_HEIGHT)
        *height = SCREEN_HEIGHT - r;

    /* ---- left clip ---- */
    /*If starting from left then, skip the off-screena and draw remaining*/
    if (c < 0)
    {
        UINT16 s = -c;
        if (s >= sprite_width)
        {
            return 0;
        }
        *x_skip = s;
        c = 0;
    }

    /* ---- right clip ---- */
    /*f the sprite starts at or past the right edge, draw nothing*/
    if (c >= SCREEN_WIDTH)
    {
        return 0;
    }

    {
        /*calculating the visible width within the border*/
        UINT16 visible = SCREEN_WIDTH - c;
        UINT16 remaining = sprite_width - *x_skip;

        if (visible > remaining)
        {
            visible = remaining;
        }
        *row = r;
        *col = c;
        return visible;
    }
}

void plot_bitmap_8(UINT8 *base, INT16 row, INT16 col, UINT16 height, const UINT8 *bitmap_8)
{
    UINT16 r, byte_col, bit_shift, visible, x_skip, y_skip;
    UINT32 offset;
    UINT8 *dest;
    UINT8 src, mask;

    visible = clip_left_top_right_bottom(&row, &col, &height, 8, &x_skip, &y_skip);
    if (visible == 0)
    {
        return;
    }

    bitmap_8 += y_skip; /*skip the off-screen rows*/
    byte_col = col >> 3;
    bit_shift = col & 7;

    for (r = 0; r < height; r++)
    {
        /*calculate start add. of row*/
        offset = (row + r) * SCREEN_BYTES_PER_ROW + byte_col;
        dest = base + offset;
        src = bitmap_8[r];
        /*left clipped*/
        if (x_skip != 0)
            src = src << x_skip;
        /*right clipped*/
        if (visible < 8 - x_skip)
        {
            mask = 0xFF << (8 - visible);
            src &= mask;
        }
        /*regular printing*/
        if (bit_shift == 0)
        {
            *dest |= src;
        }
        else
        {
            *dest |= src >> bit_shift;
            /*writing clipped sprite*/
            if (visible + bit_shift > 8 && byte_col + 1 < SCREEN_BYTES_PER_ROW)
            {
                dest[1] |= src << (8 - bit_shift);
            }
        }
    }
}
void clear_screen(UINT32 *base)
{
    int i;
    UINT32 *loc;
    i = 0;
    loc = base;
    while (i++ < LONGS_PER_SCREEN)
        *(loc++) = 0;
}
