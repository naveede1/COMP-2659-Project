#include "raster.h"
#include <stdio.h>
#include <osbind.h>

#define BYTES_PER_SCREEN 16000 /*Set the Constant Value*/

int main() {

    UINT32 *base = Physbase();
    clear_screen(base);

    return 0;
}

void clear_screen(UINT32 *base) {

       register int i = 0;
       register UINT32 *loc = base;

       while (i++ < BYTES_PER_SCREEN) {
	       *(loc++) = 0;
       }
}
