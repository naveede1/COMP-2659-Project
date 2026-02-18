#include "raster.h"
#include <stdio.h>
#include <osbind.h>

#define BYTES_PER_SCREEN 32000 
#define SCREEN_WIDTH 640 
#define SCREEN_LENGTH 400

int main() {

    UINT16 r = 48;
    UINT16 c = 87;
    UINT16 l = 22;
    UINT16 w = 40;
    UINT32 *base = Physbase();

    /* clear_screen(base);*/

    clear_region(base, r, c, l, w);

    return 0;
}

void clear_screen(UINT32 *base) {

    int i = 0;
    UINT32 *loc = base;

    while (i++ < (BYTES_PER_SCREEN/2)) {
	    *(loc++) = 0;
    }
}

void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width) {

    int i;
    int j;

    UINT32 *loc = base + (row - 1) * 5 + (col - 1);

    for (i = 0; i < length; i++) { /* For every row in the Region */
    
        for (j = 0; j < width; j++) {

            *(loc++) = 0;

        }
        
        *loc = *loc + SCREEN_WIDTH - width;

    }    
}bran
