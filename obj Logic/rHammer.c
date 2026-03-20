#include "rHammer.h"

void renderHammer(Hammer hammer, UINT32 *base) {

    if (hammer.visible == 1) {
        if (hammer.state == 0){
            plot_bitmap_16(base, hammer.posY, hammer.posX, 16, hammer_floatBM);
        }
    }
} 