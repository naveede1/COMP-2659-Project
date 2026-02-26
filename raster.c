#include "raster.h"
#include <osbind.h>
#include <linea.h>

#define SCREEN_BYTES_PER_ROW 80
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BYTES_PER_SCREEN 32000
#define LONGS_PER_SCREEN 8000

void plot_character(UINT8 *base, UINT16 row, UINT16 col, char c){
    UINT8 *font;
    UINT16 byte_col, bit_shift, r;
    UINT32 offset;
    UINT8 *dest;
    UINT8 src;
    /*Check if it is within the screen boundaries*/
    if (row >= SCREEN_HEIGHT || col >= SCREEN_WIDTH){
        return;
    }
    font = (UINT8 *)V_FNT_AD; /*Get the start add. of font table*/
    byte_col = (UINT16)(col >> 3);
    bit_shift = (UINT16)(col & 7);
    for (r = 0; r < 16; r++) {
        if ((UINT16)(row + r) >= SCREEN_HEIGHT){
            return;
        }
        /* row r of glyph c: font[c + 256 * r] ?//from lab*/
        src = font[(UINT16)(UINT8)c + (UINT16)(256 * r)];
        offset = (UINT32)(row + r) * SCREEN_BYTES_PER_ROW + byte_col;
        dest = base + offset;
        if (bit_shift == 0){
            dest[0] |= src;
        }
        else{
            dest[0] |= (UINT8)(src >> bit_shift);
            if (byte_col < (SCREEN_BYTES_PER_ROW - 1)){
                dest[1] |= (UINT8)(src << (8 - bit_shift));
            }
        }
    }
}

void plot_string(UINT8 *base, UINT16 row, UINT16 col, char *str){
    while (*str){
        plot_character(base, row, col, *str++);
        col += 8; /*Move to the next character position*/
    }
}
