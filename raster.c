#include "raster.h"
#include <osbind.h>
#include <linea.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define SCREEN_BYTES_PER_ROW 80
#define LONGS_PER_SCREEN 8000

int main()
{
    UINT8 *base = Physbase();
    clear_screen((UINT32 *)base);
    plot_horizontal_line(base, 50, -50, 200);
    plot_horizontal_line(base, 100, 500, 300);
    plot_horizontal_line(base, -10, 200, 200);
    plot_horizontal_line(base, 410, 200, 200);
    return 0;
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

void plot_horizontal_line(UINT32 *base, INT16 row, INT16 col, UINT16 length)
{
    UINT8 *base8 = (UINT8 *)base;

    UINT16 visible, x_skip, y_skip;
    UINT16 h = 1; /* treat the line as a 1-pixel-tall “sprite” */

    /* clip using your existing function */
    visible = clip_left_top_right_bottom(&row, &col, &h, length, &x_skip, &y_skip);
    if (visible == 0)
        return; /* fully off-screen */
    /* after clipping, h should be 1; if not, it's off-screen vertically */
    if (h == 0)
        return;

    /* draw visible pixels starting at (row, col) */
    {
        UINT16 start_byte = ((UINT16)col) >> 3;
        UINT16 end_byte = (UINT16)(((UINT16)col + visible - 1) >> 3);

        UINT8 start_bit = ((UINT16)col) & 7;
        UINT8 end_bit = (((UINT16)col + visible - 1) & 7);

        UINT8 *line = base8 + (UINT32)((UINT16)row) * SCREEN_BYTES_PER_ROW;
        UINT8 *curr = line + start_byte;
        UINT8 *endp = line + end_byte;

        while (curr <= endp)
        {
            if (curr == (line + start_byte) && curr == endp)
            {
                /* all within one byte */
                UINT8 left = (UINT8)(0xFF >> start_bit);
                UINT8 right = (UINT8)(0xFF << (7 - end_bit));
                *curr |= (UINT8)(left & right);
            }
            else if (curr == (line + start_byte))
            {
                /* first byte: set from start_bit to right edge */
                *curr |= (UINT8)(0xFF >> start_bit);
            }
            else if (curr == endp)
            {
                /* last byte: set from left edge to end_bit */
                *curr |= (UINT8)(0xFF << (7 - end_bit));
            }
            else
            {
                /* middle bytes fully covered */
                *curr |= 0xFF;
            }
            curr++;
        }
    }
}

void plot_vertical_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length)
{
    UINT8 *byte_base = (UINT8 *)base;
    UINT16 i;
    UINT16 current_column;

    for (i = 0; i < length; i++)
    {
        current_column = col + i;
        *(byte_base + current_column * 80 + (row >> 3)) |= 1 << (7 - (row & 7));
    }
}

UINT16 clip_left_top_right_bottom(INT16 *row, INT16 *col, UINT16 *height, UINT16 sprite_width, UINT16 *x_skip, UINT16 *y_skip)
{
    INT16 r = *row;
    INT16 c = *col;
    UINT16 visible;
    UINT16 remaining;

    *x_skip = 0;
    *y_skip = 0;

    /*top clip*/
    if (r < 0)
    {
        UINT16 s = -r;
        if (s >= *height)
        {
            return 0;
        }
        *y_skip = s;
        *height -= s;
        r = 0;
    }

    /*bottom clipping*/
    /*same logic as top clip but just camparing with the height*/
    if (r >= SCREEN_HEIGHT)
    {
        return 0;
    }
    if (r + *height > SCREEN_HEIGHT)
    {
        *height = SCREEN_HEIGHT - r;
    }
    /*left cliping */
    /*If start from left, skip the off-screen and draw remaining*/
    if (c < 0)
    {
        UINT16 s;
        s = -c;
        if (s >= sprite_width)
        {
            return 0;
        }
        *x_skip = s;
        c = 0;
    }

    /*right clipping*/
    if (c >= SCREEN_WIDTH)
    {
        return 0;
    }

    /*calculating the visible width within the border*/
    visible = SCREEN_WIDTH - c;
    remaining = sprite_width - *x_skip;

    if (visible > remaining)
    {
        visible = remaining;
    }
    *row = (UINT16)r;
    *col = (UINT16)c;
    return visible;
}
