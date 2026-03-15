#include <stdio.h>
#include "raster.h"
#include <osbind.h>

static const UINT8 smiley_bitmap[8] = {
    0x3C,
    0x42,
    0xA5,
    0x81,
    0xA5,
    0x99,
    0x42,
    0x3C,
};

int main()
{

    UINT8 *base = Physbase();
    clear_screen((UINT32 *)base);
    /* fully visible smiley at (20,20) */
    plot_bitmap_8(base, 20, 20, 8, smiley_bitmap);

    /* right clipped: col=636 means only 4 pixels visible before right edge */
    plot_bitmap_8(base, 141, 636, 8, smiley_bitmap);

    /* top clipped: row=-5 means top 5 rows are off screen */
    plot_bitmap_8(base, -5, 10, 8, smiley_bitmap);

    /* left clipped: col=-3 means leftmost 3 pixels are off screen */
    plot_bitmap_8(base, 10, -3, 8, smiley_bitmap);

    /* bottom clipped: row=396 means bottom 4 rows fall off screen */
    plot_bitmap_8(base, 396, 20, 8, smiley_bitmap);

    return 0;
}
