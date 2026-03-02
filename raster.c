#include "raster.h"
#include <osbind.h>
#include <linea.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define SCREEN_BYTES_PER_ROW 80
#define LONGS_PER_SCREEN 8000

int main()
{
    UINT8 *base8 = Physbase();
    clear_screen((UINT32 *)base8);
	plot_string(base8, 50, 50, "HELLO");

    /* ============================= */
    /* Near right edge (clipping)    */
    /* ============================= */
    plot_string(base8, 80, 620, "WORLD");

    /* ============================= */
    /* Near bottom edge (clipping)   */
    /* ============================= */
    plot_string(base8, 390, 100, "BOTTOM");

    /* ============================= */
    /* Partially off right           */
    /* ============================= */
    plot_string(base8, 150, 630, "CLIP");

    /* ============================= */
    /* Completely off right          */
    /* ============================= */
    plot_string(base8, 200, 700, "HIDDEN");
    linea0();
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
    if (visible == 0) return;
    if (h == 0) return;

    start_byte = ((UINT16)c) >> 3;
    end_byte   = (UINT16)(((UINT16)c + visible - 1) >> 3);

    start_bit = (UINT8)(((UINT16)c) & 7);
    end_bit   = (UINT8)((((UINT16)c + visible - 1) & 7));

    line = base8 + ((UINT32)((UINT16)r) * SCREEN_BYTES_PER_ROW);
    curr = line + start_byte;
    endp = line + end_byte;

    while (curr <= endp){
    if (curr == (line + start_byte) && curr == endp) {
		UINT8 left, right;
        left  = (UINT8)(0xFF >> start_bit);
        right = (UINT8)(0xFF << (7 - end_bit));
        *curr |= (UINT8)(left & right);
	}
	else if (curr == (line + start_byte)){
            *curr |= (UINT8)(0xFF >> start_bit);		
	}
    else if (curr == endp){
        *curr |= (UINT8)(0xFF << (7 - end_bit));
	}
    else{
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
    UINT16 byte_col;
    UINT8 bit_mask;
    UINT8 *p;

    base8 = (UINT8 *)base;

    r = (INT16)row;
    c = (INT16)col;
    h = length;

    visible = clip_left_top_right_bottom(&r, &c, &h, 1, &x_skip, &y_skip);
    if (visible == 0 || h == 0) return;

    byte_col = ((UINT16)c) >> 3;
    bit_mask = (UINT8)(1 << (7 - (((UINT16)c) & 7)));

    for (i = 0; i < h; i++){
        p = base8 + (UINT32)((UINT16)r + i) * SCREEN_BYTES_PER_ROW + byte_col;
        *p |= bit_mask;
    }
}
void plot_line(UINT32 *base, INT16 start_row, INT16 start_col, INT16 end_row, INT16 end_col)
{
    UINT8 *byte_base = (UINT8 *)base;
    int abs_distance_x, abs_distance_y;
    int step_x, step_y;
    int error, temp_error;
    UINT16 current_row = start_row;
    UINT16 current_col = start_col;

    abs_distance_x = end_row > start_row ? end_row - start_row : start_row - end_row;
    abs_distance_y = end_col > start_col ? end_col - start_col : start_col - end_col;

    step_x = start_row < end_row ? 1 : -1;
    step_y = start_col < end_col ? 1 : -1;

    error = abs_distance_x - abs_distance_y;

    while (1){
		/* Bresenham's line algorithm */
        if ((INT16)current_row >= 0 && current_row < SCREEN_HEIGHT &&
            (INT16)current_col >= 0 && current_col < SCREEN_WIDTH){
            *(byte_base + current_col * 80 + (current_row >> 3)) |= 1 << (7 - (current_row & 7));
        }

        if (current_row == end_row && current_col == end_col){
            break;
        }
        temp_error = 2 * error;
        if (temp_error > -abs_distance_y){
            error -= abs_distance_y;
            current_row += step_x;
        }

        if (temp_error < abs_distance_x){
            error += abs_distance_x;
            current_col += step_y;
        }
    }
}
	
void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width) {
    UINT16 right_vertical_line_row = row + width - 1;    
    UINT16 bottom_horizontal_line_col = col + length - 1;
                                                  
    plot_horizontal_line(base, row, col, width);
    plot_horizontal_line(base, row, bottom_horizontal_line_col, width);
    plot_vertical_line(base, row, col, length);
    plot_vertical_line(base, right_vertical_line_row, col, length);
}

void plot_square(UINT32 *base, UINT16 row, UINT16 col, UINT16 side) {
    UINT16 right_vertical_line_row = row + side - 1;    
    UINT16 bottom_horizontal_line_col = col + side - 1;

    plot_horizontal_line(base, row, col, side);
    plot_horizontal_line(base, row, bottom_horizontal_line_col, side);
    plot_vertical_line(base, row, col, side);
    plot_vertical_line(base, right_vertical_line_row, col, side);
}

void plot_triangle(UINT32 *baseptr, UINT16 row, UINT16 col, UINT16 base, UINT16 height, UINT8 direction) {
    UINT16 diag_start_row, diag_start_col;
    UINT16 diag_end_row, diag_end_col;
    
    if (direction == 0) {
        plot_vertical_line(baseptr, row, col, height);
        plot_horizontal_line(baseptr, row, col, base);
        
        diag_start_row = row + base - 1;
        diag_start_col = col;
        diag_end_row = row;
        diag_end_col = col + height - 1;
        plot_line(baseptr, diag_start_row, diag_start_col, diag_end_row, diag_end_col);
        
    } else if (direction == 1) {
        plot_vertical_line(baseptr, row, col, height);
        plot_horizontal_line(baseptr, row - base + 1, col, base);
        
        diag_start_row = row - base + 1;
        diag_start_col = col;
        diag_end_row = row;
        diag_end_col = col + height - 1;
        plot_line(baseptr, diag_start_row, diag_start_col, diag_end_row, diag_end_col);
        
    } else if (direction == 2) {
        plot_vertical_line(baseptr, row, col - height + 1, height);
        plot_horizontal_line(baseptr, row, col, base);

        diag_start_row = row + base - 1;
        diag_start_col = col;
        diag_end_row = row;
        diag_end_col = col - height + 1;
        plot_line(baseptr, diag_start_row, diag_start_col, diag_end_row, diag_end_col);
        
    } else if (direction == 3) {
        plot_vertical_line(baseptr, row, col - height + 1, height);
        plot_horizontal_line(baseptr, row - base + 1, col, base);
        
        diag_start_row = row - base + 1;
        diag_start_col = col;
        diag_end_row = row;
        diag_end_col = col - height + 1;
        plot_line(baseptr, diag_start_row, diag_start_col, diag_end_row, diag_end_col);
    }
}

void plot_character(UINT8 *base, UINT16 row, UINT16 col, char c)
{
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
    if (visible == 0 || h == 0) return;

    font = (UINT8 *)V_FNT_AD;

    byte_col = (UINT16)cc >> 3;
    bit_shift = (UINT16)cc & 7;

    for (r = 0; r < h; r++)
    {
        /* fetch correct font row (include y_skip) */
        src = font[(UINT16)(UINT8)c + (UINT16)(256 * (r + y_skip))];

        /* apply left clip */
        if (x_skip != 0)
            src = (UINT8)(src << x_skip);

        /* apply right clip */
        if (visible < (UINT16)(8 - x_skip))
        {
            UINT8 mask;
            mask = (UINT8)(0xFFu << (8 - visible));
            src = (UINT8)(src & mask);
        }

        offset = (UINT32)((UINT16)rr + r) * SCREEN_BYTES_PER_ROW + byte_col;
        dest = base + offset;

        if (bit_shift == 0)
        {
            dest[0] |= src;
        }
        else
        {
            dest[0] |= (UINT8)(src >> bit_shift);

            /* only write into next byte if it stays on the row */
            if ((visible + bit_shift > 8) && (byte_col < (SCREEN_BYTES_PER_ROW - 1)))
                dest[1] |= (UINT8)(src << (8 - bit_shift));
        }
    }
}

void plot_string(UINT8 *base, UINT16 row, UINT16 col, char *str)
{
    while (*str)
    {
        if (col >= SCREEN_WIDTH) return;
        plot_character(base, row, col, *str++);
        col = (UINT16)(col + 8);
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

