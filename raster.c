#include "raster.h"
#include <osbind.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BYTES_PER_SCREEN 32000

int main() {

    	UINT8 *base = Physbase();
        UINT16 row = 17;
        UINT16 col = 26;

        plot_pixel(base, row, col);

    return 0;
}

void plot_pixel(UINT8 *base, UINT16 row, UINT16 col) {
    if (row >= 0 && row < SCREEN_WIDTH && col >= 0 && col < SCREEN_HEIGHT){
        *(base + col * 80 + (row >> 3)) |= 1 << (7 - (row & 7));
    }
}