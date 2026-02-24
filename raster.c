#include "raster.h"
#include <osbind.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define SCREEN_BYTES_PER_ROW 80

int main()
{
    UINT8 *base = Physbase();

    plot_bitmap_8(base, 141, 636, 8, smiley_bitmap);
    plot_bitmap_16((UINT16 *)base, 241, 636, 16, invader_bitmap);
    plot_bitmap_32((UINT32 *)base, 341, 636, 32, block_bitmap);
    return 0;
}

UINT16 clip_right_bottom(UINT16 row, UINT16 col, UINT16 *height, UINT16 sprite_width)
{
    UINT16 visible;
    /* bottom clip */
    if (row >= SCREEN_HEIGHT)
        return 0;

    if ((UINT32)row + (UINT32)(*height) > (UINT32)SCREEN_HEIGHT)
        *height = (UINT16)(SCREEN_HEIGHT - row);

    /* right clip */
    if (col >= SCREEN_WIDTH)
        return 0;

    /* compute visible width */

    visible = (UINT16)(SCREEN_WIDTH - col);

    if (visible > sprite_width)
        visible = sprite_width;

    return visible;
}

void plot_bitmap_8(UINT8 *base, UINT16 row, UINT16 col, UINT16 height, const UINT8 *bitmap_8)
{

    UINT16 byte_col;
    UINT16 bit_shift;
    UINT16 r;
    UINT32 offset;
    UINT8 *dest;
    UINT8 src;
    UINT8 mask;
    UINT16 visible;
    visible = clip_right_bottom(row, col, &height, 8);
    if (visible == 0)
        return;

    byte_col = (UINT16)(col >> 3);
    bit_shift = (UINT16)(col & 7);

    for (r = 0; r < height; r++)
    {
        offset = (UINT32)(row + r) * (UINT32)SCREEN_BYTES_PER_ROW + (UINT32)byte_col;
        dest = base + offset;

        src = bitmap_8[r];

        /* mask off pixels past right edge */
        if (visible < 8)
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
            *dest = (UINT8)(*dest | (UINT8)(src >> bit_shift));

            if (byte_col + 1 < SCREEN_BYTES_PER_ROW)
            {
                *(dest + 1) = (UINT8)(*(dest + 1) | (UINT8)(src << (8 - bit_shift)));
            }
        }
    }
}

void plot_bitmap_16(UINT16 *base16, UINT16 row, UINT16 col, UINT16 height, const UINT16 *bitmap_16)
{
    UINT16 r;
    UINT16 byte_col;
    UINT16 bit_shift;
    UINT32 row_offset;
    UINT8 *row_ptr;
    UINT8 *dest;
    UINT16 src16;
    UINT16 mask16;
    UINT8 b0, b1, b2;
    UINT16 visible;
    visible = clip_right_bottom(row, col, &height, 16);
    if (visible == 0)
        return;
    byte_col = col >> 3;
    bit_shift = col & 7;

    for (r = 0; r < height; r++)
    {
        row_offset = (UINT32)(row + r) * (UINT32)SCREEN_BYTES_PER_ROW;
        row_ptr = (UINT8 *)base16 + row_offset;
        dest = row_ptr + byte_col;

        src16 = bitmap_16[r];

        /* mask off pixels past right edge (keep leftmost 'visible' bits) */
        if (visible < 16)
        {
            mask16 = (UINT16)(0xFFFFu << (16 - visible));
            src16 = (UINT16)(src16 & mask16);
        }

        /* shift into position */
        if (bit_shift != 0)
            src16 = (UINT16)(src16 >> bit_shift);

        /* split into bytes (big-endian bit order within the 16-bit row) */
        b0 = (UINT8)(src16 >> 8);
        b1 = (UINT8)(src16 & 0xFF);

        /* OR into framebuffer bytes, with carry into next byte if needed */
        dest[0] |= b0;

        if (byte_col + 1 < SCREEN_BYTES_PER_ROW)
            dest[1] |= b1;

        /* If bit_shift != 0, some bits spill into a 3rd byte */
        if (bit_shift != 0)
        {
            UINT32 stage;
            stage = (UINT32)bitmap_16[r];
            if (visible < 16)
                stage &= (UINT32)mask16;
            stage >>= bit_shift;        /* aligned to dest[0] bit7 */
            b2 = (UINT8)(stage & 0xFF); /* lowest 8 bits land in dest[2] */

            if (byte_col + 2 < SCREEN_BYTES_PER_ROW)
                dest[2] |= b2;
        }
    }
}

void plot_bitmap_32(UINT32 *base32, UINT16 row, UINT16 col, UINT16 height, const UINT32 *bitmap_32)
{
    UINT16 r;
    UINT16 byte_col;
    UINT16 bit_shift;
    UINT32 row_offset;
    UINT8 *row_ptr;
    UINT8 *dest;
    UINT32 src32;
    UINT32 mask32;
    UINT32 stage;
    UINT8 b0, b1, b2, b3, b4;
    UINT16 visible;
    visible = clip_right_bottom(row, col, &height, 32);
    if (visible == 0)
        return;

    byte_col = (UINT16)(col >> 3);
    bit_shift = (UINT16)(col & 7);

    for (r = 0; r < height; r++)
    {
        row_offset = (UINT32)(row + r) * (UINT32)SCREEN_BYTES_PER_ROW;
        row_ptr = (UINT8 *)base32 + row_offset;
        dest = row_ptr + byte_col;

        src32 = bitmap_32[r];

        /* mask off pixels past right edge (keep leftmost 'visible' bits) */
        if (visible < 32)
        {
            mask32 = (UINT32)(0xFFFFFFFFu << (32 - visible));
            src32 = (UINT32)(src32 & mask32);
        }

        /* Use a 40-bit staging in a 32-bit var by OR-ing bytes after shifting */
        stage = src32;
        if (bit_shift != 0)
            stage >>= bit_shift;

        b0 = (UINT8)(stage >> 24);
        b1 = (UINT8)(stage >> 16);
        b2 = (UINT8)(stage >> 8);
        b3 = (UINT8)(stage);

        dest[0] |= b0;
        if (byte_col + 1 < SCREEN_BYTES_PER_ROW)
            dest[1] |= b1;
        if (byte_col + 2 < SCREEN_BYTES_PER_ROW)
            dest[2] |= b2;
        if (byte_col + 3 < SCREEN_BYTES_PER_ROW)
            dest[3] |= b3;

        /* spill into 5th byte when not byte-aligned */
        if (bit_shift != 0)
        {
            /* compute spill byte from masked original */
            UINT32 spill_stage;
            spill_stage = bitmap_32[r];
            if (visible < 32)
                spill_stage &= mask32;
            spill_stage >>= bit_shift;
            b4 = (UINT8)(spill_stage & 0xFF);

            if (byte_col + 4 < SCREEN_BYTES_PER_ROW)
                dest[4] |= b4;
        }
    }
}
