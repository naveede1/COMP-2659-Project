#include "raster.h"
#include <stdio.h>
#include <osbind.h>

#define LONGS_PER_SCREEN 8000
#define SCREEN_BYTES_PER_ROW 80
#define SCREEN_HEIGHT 400

#define BYTES_PER_SCREEN 32000 
#define SCREEN_WIDTH 640 
#define SCREEN_LENGTH 400



void clear_screen(UINT32 *base){
    int i;
    UINT32 *loc;
    i = 0;
    loc = base;
    while (i++ < LONGS_PER_SCREEN)
        *(loc++) = 0;
}

void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width) {
    UINT8 *base8 = (UINT8 *)base;
    UINT16 visible;
    UINT16 x_skip, y_skip;
    UINT8 *line;
    UINT8 *start;
    UINT8 *end;
    UINT8 *curr;
    UINT16 start_byte, end_byte;
    UINT8 start_bit, end_bit;
    UINT16 r;
    UINT16 h = length;
    INT16 r0 = (INT16)row;
    INT16 c0 = (INT16)col;

    visible = clip_left_top_right_bottom(&r0, &c0, &h, width, &x_skip, &y_skip);
    if (visible == 0 || h == 0)
        return;

    start_byte = ((UINT16)c0) >> 3;
    end_byte = (UINT16)(((UINT16)c0 + visible - 1) >> 3);

    start_bit = (UINT8)(((UINT16)c0) & 7);
    end_bit = (UINT8)((((UINT16)c0 + visible - 1) & 7));
    /* clear length rows, start from r0*/
    for (r = 0; r < h; r++) {
        line = base8 + (UINT32)((UINT16)r0 + r) * SCREEN_BYTES_PER_ROW;
        start = line + start_byte;
        end = line + end_byte;
        curr = start;
        while (curr <= end) {
            if (curr == start && curr == end) {
                UINT8 left, right, mask;
                left = (UINT8)(0xFF >> start_bit);
                right = (UINT8)(0xFF << (7 - end_bit));
                mask = (UINT8)(left & right);
                *curr &= (UINT8)~mask;
            } else if (curr == start) {
                UINT8 mask;
                mask = (UINT8)(0xFF >> start_bit);
                *curr &= (UINT8)~mask;
            } else if (curr == end) {
                UINT8 mask;
                mask = (UINT8)(0xFF << (7 - end_bit));
                *curr &= (UINT8)~mask;
            } else {
                *curr = 0x00;
            }
            curr++;
        }
    }
}

void plot_pixel(UINT8 *base, UINT16 row, UINT16 col) {
    if (row >= 0 && row < SCREEN_WIDTH && col >= 0 && col < SCREEN_HEIGHT) {
        *(base + col * 80 + (row >> 3)) |= 1 << (7 - (row & 7));
    }
}

void plot_horizontal_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length) {
    UINT8 *base8;
    INT16 r;
    INT16 c;
    UINT16 visible, x_skip, y_skip;
    UINT16 h;
    UINT16 start_byte, end_byte;
    UINT8 start_bit, end_bit;
    UINT8 *line;
    UINT8 *curr;
    UINT8 *endp;
    base8 = (UINT8 *)base;

    /* treat line as 1-tall sprite */
    r = (INT16)row;
    c = (INT16)col;
    h = 1;
    visible = clip_left_top_right_bottom(&r, &c, &h, length, &x_skip, &y_skip);
    if (visible == 0)
        return;
    if (h == 0)
        return;

    start_byte = ((UINT16)c) >> 3;
    end_byte = (UINT16)(((UINT16)c + visible - 1) >> 3);

    start_bit = (UINT8)(((UINT16)c) & 7);
    end_bit = (UINT8)((((UINT16)c + visible - 1) & 7));

    line = base8 + ((UINT32)((UINT16)r) * SCREEN_BYTES_PER_ROW);
    curr = line + start_byte;
    endp = line + end_byte;

    while (curr <= endp) {
        if (curr == (line + start_byte) && curr == endp) {
            UINT8 left, right;
            left = (UINT8)(0xFF >> start_bit);
            right = (UINT8)(0xFF << (7 - end_bit));
            *curr |= (UINT8)(left & right);
        } else if (curr == (line + start_byte)) {
            *curr |= (UINT8)(0xFF >> start_bit);
        } else if (curr == endp) {
            *curr |= (UINT8)(0xFF << (7 - end_bit));
        } else {
            *curr |= 0xFF;
        }
        curr++;
    }
}

void plot_vertical_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length) {
    UINT8 *base8;
    INT16 r;
    INT16 c;
    UINT16 h;
    UINT16 x_skip, y_skip;
    UINT16 visible;
    UINT16 i;

    base8 = (UINT8 *)base;

    r = (INT16)row;
    c = (INT16)col;
    h = length;

    visible = clip_left_top_right_bottom(&r, &c, &h, 1, &x_skip, &y_skip);
    if (visible == 0 || h == 0)
        return;

    for (i = 0; i < h; i++) {
        INT16 rr = (INT16)(r + i);

        if (rr >= 0 && rr < SCREEN_HEIGHT) {
            base8[(UINT32)rr * SCREEN_BYTES_PER_ROW + ((UINT16)c >> 3)] |=
                (UINT8)(1 << (7 - ((UINT16)c & 7)));
        }
    }
}

void plot_line(UINT32 *base, INT16 start_row, INT16 start_col, INT16 end_row, INT16 end_col) {
    UINT8 *byte_base;
    int abs_distance_x, abs_distance_y;
    int step_x, step_y;
    int error, temp_error;
    INT16 current_row, current_col;

    byte_base = (UINT8 *)base;

    current_row = start_row;
    current_col = start_col;

    abs_distance_x = end_row > start_row ? end_row - start_row : start_row - end_row;
    abs_distance_y = end_col > start_col ? end_col - start_col : start_col - end_col;

    step_x = start_row < end_row ? 1 : -1;
    step_y = start_col < end_col ? 1 : -1;

    error = abs_distance_x - abs_distance_y;

    while (1) {
        /* clip: only plot if on-screen */
        if (current_row >= 0 && current_row < SCREEN_HEIGHT && current_col >= 0 && current_col < SCREEN_WIDTH) {
            /* correct 1bpp address: row*80 + (col>>3), bit uses col */
            byte_base[(UINT32)current_row * SCREEN_BYTES_PER_ROW + ((UINT16)current_col >> 3)] |=
                (UINT8)(1 << (7 - ((UINT16)current_col & 7)));
        }

        if (current_row == end_row && current_col == end_col)
            break;

        temp_error = 2 * error;

        if (temp_error > -abs_distance_y) {
            error -= abs_distance_y;
            current_row = (INT16)(current_row + step_x);
        }

        if (temp_error < abs_distance_x) {
            error += abs_distance_x;
            current_col = (INT16)(current_col + step_y);
        }
    }
}

void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width) {
    UINT16 bottom_row = row + length - 1;
    UINT16 right_col = col + width - 1;

    /* top + bottom */
    plot_horizontal_line(base, row, col, width);
    plot_horizontal_line(base, bottom_row, col, width);

    /* left + right */
    plot_vertical_line(base, row, col, length);
    plot_vertical_line(base, row, right_col, length);
}

void plot_square(UINT32 *base, UINT16 row, UINT16 col, UINT16 side) {
    UINT16 bottom_row = row + side - 1;
    UINT16 right_col = col + side - 1;

    plot_horizontal_line(base, row, col, side);
    plot_horizontal_line(base, bottom_row, col, side);

    plot_vertical_line(base, row, col, side);
    plot_vertical_line(base, row, right_col, side);
}

void plot_triangle(UINT32 *baseptr, UINT16 row, UINT16 col, UINT16 base, UINT16 height, UINT8 direction) {
    INT16 r0, c0, r1, c1, r2, c2;

    if (direction == 0) {
        /* right angle at (row,col), base to right, height down */
        r0 = (INT16)row;
        c0 = (INT16)col;
        r1 = (INT16)row;
        c1 = (INT16)(col + base - 1);
        r2 = (INT16)(row + height - 1);
        c2 = (INT16)col;
        plot_horizontal_line(baseptr, row, col, base);
        plot_vertical_line(baseptr, row, col, height);
        plot_line(baseptr, r1, c1, r2, c2);
    } else if (direction == 1) {
        /* right angle at (row,col), base to left, height down */
        r0 = (INT16)row;
        c0 = (INT16)col;
        r1 = (INT16)row;
        c1 = (INT16)(col - (INT16)base + 1);
        r2 = (INT16)(row + height - 1);
        c2 = (INT16)col;

        plot_horizontal_line(baseptr, row, (INT16)(col - base + 1), base);
        plot_vertical_line(baseptr, row, col, height);
        plot_line(baseptr, r1, c1, r2, c2);
    } else if (direction == 2) {
        /* right angle at (row,col), base to right, height up */
        r0 = (INT16)row;
        c0 = (INT16)col;
        r1 = (INT16)row;
        c1 = (INT16)(col + base - 1);
        r2 = (INT16)(row - (INT16)height + 1);
        c2 = (INT16)col;

        plot_horizontal_line(baseptr, row, col, base);
        plot_vertical_line(baseptr, (INT16)(row - height + 1), col, height);
        plot_line(baseptr, r1, c1, r2, c2);
    } else if (direction == 3) {
        /* right angle at (row,col), base to left, height up */
        r0 = (INT16)row;
        c0 = (INT16)col;
        r1 = (INT16)row;
        c1 = (INT16)(col - (INT16)base + 1);
        r2 = (INT16)(row - (INT16)height + 1);
        c2 = (INT16)col;

        plot_horizontal_line(baseptr, row, (INT16)(col - base + 1), base);
        plot_vertical_line(baseptr, (INT16)(row - height + 1), col, height);
        plot_line(baseptr, r1, c1, r2, c2);
    }
}

UINT16 clip_left_top_right_bottom(INT16 *row, INT16 *col, UINT16 *height, UINT16 sprite_width, UINT16 *x_skip, UINT16 *y_skip) {
    INT16 r = *row;
    INT16 c = *col;
    UINT16 visible;
    UINT16 remaining;

    *x_skip = 0;
    *y_skip = 0;

    /*top clip*/
    if (r < 0) {
        UINT16 s = -r;
        if (s >= *height)
            return 0;
        *y_skip = s;
        *height -= s;
        r = 0;
    }

    /*bottom clipping*/
    /*same logic as top clip but just camparing with the height*/
    if (r >= SCREEN_HEIGHT) {
        return 0;
    } 
    
    if (r + *height > SCREEN_HEIGHT) {
        *height = SCREEN_HEIGHT - r;
    }
    /*left clipping */
    /*If start from left, skip the off-screen and draw remaining*/
    if (c < 0) {
        UINT16 s;
        s = -c;
        if (s >= sprite_width) {
            return 0;
        }
        *x_skip = s;
        c = 0;
    }

    /*right clipping*/
    if (c >= SCREEN_WIDTH) {
        return 0;
    }

    /*calculating the visible width within the border*/
    visible = SCREEN_WIDTH - c;
    remaining = sprite_width - *x_skip;

    if (visible > remaining) {
        visible = remaining;
    }
    *row = (UINT16)r;
    *col = (UINT16)c;
    return visible;
}

void plot_bitmap_8(UINT8 *base, INT16 row, INT16 col, UINT16 height, const UINT8 *bitmap_8) {
    UINT16 r, byte_col, bit_shift, visible, x_skip, y_skip;
    UINT32 offset;
    UINT8 *dest;
    UINT8 src, mask;

    visible = clip_left_top_right_bottom(&row, &col, &height, 8, &x_skip, &y_skip);
    if (visible == 0) { /*out of bounds, donot draw*/
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
        if (x_skip != 0) {
            src = src << x_skip;
        }
        /*right clipped*/
        if (visible < 8 - x_skip) {
            mask = 0xFF << (8 - visible);
            src &= mask;
        }
        /*regular printing*/
        if (bit_shift == 0) {
            *dest |= src;
        } else {
            *dest |= src >> bit_shift;
            /*writing clipped sprite*/
            if (visible + bit_shift > 8 && byte_col + 1 < SCREEN_BYTES_PER_ROW) {
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
    if (visible == 0)
        return;

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
    if (visible == 0) {
        return;
    }
    bitmap_32 += y_skip;
    byte_col = col >> 3;
    bit_shift = col & 7;

    for (r = 0; r < height; r++) {
        UINT8 *dest = base8 + (UINT32)(row + r) * SCREEN_BYTES_PER_ROW + byte_col;
        UINT32 src = bitmap_32[r];

        /*left clipping*/
        if (x_skip != 0) {
            src = src << x_skip;
        }

        /*right clipping*/
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

void plot_character(UINT8 *base, INT16 row, INT16 col, char c) {
    UINT8 *font;
    UINT16 byte_col, bit_shift;
    UINT16 r;
    UINT32 offset;
    UINT8 *dest;
    UINT8 src;

    INT16 rr;
    INT16 cc;
    UINT16 h;
    UINT16 visible, x_skip, y_skip;

    /* set up for clipping: glyph is 8 wide, 16 high */
    rr = (INT16)row;
    cc = (INT16)col;
    h = 16;

    visible = clip_left_top_right_bottom(&rr, &cc, &h, 8, &x_skip, &y_skip);
    if (visible == 0 || h == 0)
        return;
    font = (UINT8 *)V_FNT_AD;

    byte_col = (UINT16)cc >> 3;
    bit_shift = (UINT16)cc & 7;

    for (r = 0; r < h; r++) {
        /*fetch correct font row*/
        src = font[(UINT16)(UINT8)c + (UINT16)(256 * (r + y_skip))];
        /*Left clip*/
        if (x_skip != 0)
            src = (UINT8)(src << x_skip);

        /* apply right clip */
        if (visible < (UINT16)(8 - x_skip)) {
            UINT8 mask;
            mask = (UINT8)(0xFFu << (8 - visible));
            src = (UINT8)(src & mask);
        }

        offset = (UINT32)((UINT16)rr + r) * SCREEN_BYTES_PER_ROW + byte_col;
        dest = base + offset;

        if (bit_shift == 0) {
            dest[0] |= src;
        } else {
            dest[0] |= (UINT8)(src >> bit_shift);

            /* only write into next byte if it stays on the row */
            if ((visible + bit_shift > 8) && (byte_col < (SCREEN_BYTES_PER_ROW - 1)))
                dest[1] |= (UINT8)(src << (8 - bit_shift));
        }
    }
}

void plot_string(UINT8 *base, INT16 row, INT16 col, char *str) {
    while (*str) {
        if (col >= SCREEN_WIDTH)
            return;
        plot_character(base, row, col, *str++);
        col = (UINT16)(col + 8);
    }
}
