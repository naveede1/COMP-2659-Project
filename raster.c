#include "raster.h"
#include <osbind.h>
#include <linea.h>

#define SCREEN_BYTES_PER_ROW 80
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BYTES_PER_SCREEN 32000
#define LONGS_PER_SCREEN 8000

int main(void)
{
    UINT8 *base = (UINT8 *)Physbase();
    UINT32 *base32 = (UINT32 *)base;

    linea0(); /*REQUIRED for V_FNT_AD*/
    clear_screen(base32);
    plot_character(base, 0, 0, 'A');

    Cnecin();
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

void plot_pixel(UINT8 *base, UINT16 row, UINT16 col)
{
    if (row >= 0 && row < SCREEN_WIDTH && col >= 0 && col < SCREEN_HEIGHT)
    {
        *(base + col * 80 + (row >> 3)) |= 1 << (7 - (row & 7));
    }
}

void plot_character(UINT8 *base, UINT16 row, UINT16 col, char c)
{
    UINT8 *font;
    UINT16 byte_col, bit_shift, r;
    UINT32 offset;
    UINT8 *dest;
    UINT8 src;
    /* Check if it is within the screen boundaries */
    if (row >= SCREEN_HEIGHT || col >= SCREEN_WIDTH)
        return;

    font = (UINT8 *)V_FNT_AD; /* get start add. of font table */
    byte_col = (UINT16)(col >> 3);
    bit_shift = (UINT16)(col & 7);

    for (r = 0; r < 16; r++)
    {
        if ((UINT16)(row + r) >= SCREEN_HEIGHT)
            return;

        /* row r of glyph c: font[c + 256*r] from lab*/
        src = font[(UINT16)(UINT8)c + (UINT16)(256 * r)];

        offset = (UINT32)(row + r) * SCREEN_BYTES_PER_ROW + byte_col;
        dest = base + offset;
        if (bit_shift == 0)
        {
            dest[0] |= src;
        }
        else
        {
            dest[0] |= (UINT8)(src >> bit_shift);
            if (byte_col < (SCREEN_BYTES_PER_ROW - 1))
                dest[1] |= (UINT8)(src << (8 - bit_shift));
        }
    }
}
