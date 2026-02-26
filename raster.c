#include "raster.h"
#include <osbind.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define SCREEN_BYTES_PER_ROW 80
#define LONGS_PER_SCREEN 8000


UINT16 clip_left_top_right_bottom(INT16 *row, INT16 *col, UINT16 *height,UINT16 sprite_width, UINT16 *x_skip, UINT16 *y_skip){
    INT16 r = *row;
    INT16 c = *col;
    UINT16 visible;
    UINT16 remaining;

    *x_skip = 0;
    *y_skip = 0;

    /*top clip*/
    if (r < 0){
        UINT16 s = -r;
        if (s >= *height) {
            return 0;
        }
        *y_skip = s;
        *height -= s;
        r = 0;
    }

    /*bottom clipping*/
    /*same logic as top clip but just camparing with the height*/
    if (r >= SCREEN_HEIGHT) {
        return 0;
    }
    if (r + *height > SCREEN_HEIGHT){
        *height = SCREEN_HEIGHT - r;
    }
    /*left cliping */
    /*If start from left, skip the off-screen and draw remaining*/
    if (c < 0){
        UINT16 s;
        s = -c;
        if (s >= sprite_width){
            return 0;
        }
        *x_skip = s;
        c = 0;
    }

    /*right clipping*/
    if (c >= SCREEN_WIDTH){
        return 0;
    }

    /*calculating the visible width within the border*/
    visible = SCREEN_WIDTH - c;
    remaining = sprite_width - *x_skip;

    if (visible > remaining){
        visible = remaining;
    }
    *row = (UINT16)r;
    *col = (UINT16)c;
    return visible;
}

void plot_bitmap_8(UINT8 *base, INT16 row, INT16 col, UINT16 height, const UINT8 *bitmap_8){
    UINT16 r, byte_col, bit_shift, visible, x_skip, y_skip;
    UINT32 offset;
    UINT8 *dest;
    UINT8 src, mask;

    visible = clip_left_top_right_bottom(&row, &col, &height, 8, &x_skip, &y_skip);
    if (visible == 0){ /*out of bounds, donot draw*/ 
        return;
    }

    bitmap_8 += y_skip; /*skip the off-screen rows*/
    byte_col = col >> 3;
    bit_shift = col & 7;

    for (r = 0; r < height; r++) {
        /*calculate start add. of row*/
        offset = (row + r) * SCREEN_BYTES_PER_ROW + byte_col;
        dest = base + offset;
        src = bitmap_8[r];
        /*left clipped*/
        if (x_skip != 0){
            src = src << x_skip;
        }
        /*right clipped*/
        if (visible < 8 - x_skip){
            mask = 0xFF << (8 - visible);
            src &= mask;
        }
        /*regular printing*/
        if (bit_shift == 0){
            *dest |= src;
        }
        else {
            *dest |= src >> bit_shift;
            /*writing clipped sprite*/
            if (visible + bit_shift > 8 && byte_col + 1 < SCREEN_BYTES_PER_ROW){
                dest[1] |= src << (8 - bit_shift);
            }
        }
    }
}
void plot_bitmap_16(UINT16 *base, INT16 row, INT16 col, UINT16 height, const UINT16 *bitmap_16) {
    UINT16 x_skip, y_skip, visible;
    UINT16 word_col, bit_shift, r;
    UINT8 *base8 = (UINT8 *)base;

    visible = clip_left_top_right_bottom(&row, &col, &height, 16, &x_skip, &y_skip);
    if (visible == 0) return;

    bitmap_16 += y_skip;
    word_col = col >> 4;
    bit_shift = col & 15;

    for (r = 0; r < height; r++) {
        UINT32 offset = (UINT32)(row + r) * (SCREEN_BYTES_PER_ROW / 2) + word_col;
        UINT16 *dest = (UINT16 *)base8 + offset;
        UINT16 src = bitmap_16[r];

        /* Apply left clip: shift out the skipped bits on the left */
        if (x_skip != 0) {
            src = src << x_skip;
        }

        /* Apply right clip: mask out bits beyond visible width */
        if (visible < 16 - x_skip) {
            UINT16 mask = (UINT16)(0xFFFF << (16 - visible));
            src &= mask;
        }

        if (bit_shift == 0) {
            *dest |= src;
        } else {
            *dest |= (src >> bit_shift);
            /* Write overflow into next word only if it's within screen bounds */
            if (visible + bit_shift > 16 && word_col + 1 < (SCREEN_BYTES_PER_ROW / 2)) {
                dest[1] |= (src << (16 - bit_shift));
            }
        }
    }
}

void plot_bitmap_32(UINT32 *base, INT16 row, INT16 col, UINT16 height, const UINT32 *bitmap_32) {
    UINT16 x_skip, y_skip, visible;
    UINT16 byte_col, bit_shift, r;
    UINT8 *base8 = (UINT8 *)base;
	UINT8 b0, b1, b2, b3;
    visible = clip_left_top_right_bottom(&row, &col, &height, 32, &x_skip, &y_skip);
    if (visible == 0){ 
		return;
	}
    bitmap_32 += y_skip;
    byte_col = col >> 3;
    bit_shift = col & 7;

    for (r = 0; r < height; r++) {
        UINT8 *dest = base8 + (UINT32)(row + r) * SCREEN_BYTES_PER_ROW + byte_col;
        UINT32 src = bitmap_32[r];

        /*left cliping*/
        if (x_skip != 0) {
            src = src << x_skip;
        }

        /*right cliping*/
        if (visible < 32 - x_skip) {
            UINT32 mask;
	    mask = (UINT32)(0xFFFFFFFF << (32 - (UINT32)visible));
            src &= mask;
        }

        b0 = src >> 24;
        b1 = src >> 16;
        b2 = src >> 8;
        b3 = src;

        if (bit_shift == 0) {
            dest[0] |= b0;
            dest[1] |= b1;
            dest[2] |= b2;
            dest[3] |= b3;
        } else {
            dest[0] |= (b0 >> bit_shift);
            dest[1] |= (b0 << (8 - bit_shift)) | (b1 >> bit_shift);
            dest[2] |= (b1 << (8 - bit_shift)) | (b2 >> bit_shift);
            dest[3] |= (b2 << (8 - bit_shift)) | (b3 >> bit_shift);
            /*Write overflow byte*/
            if (visible + bit_shift > 32 && byte_col + 4 < SCREEN_BYTES_PER_ROW) {
                dest[4] |= (b3 << (8 - bit_shift));
            }
        }
    }
}
