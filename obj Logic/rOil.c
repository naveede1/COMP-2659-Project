#include "rOil.h"

void renderOil(Oil oil, UINT32 *base) {

    if (oil.visible == 1){
        if (oil.state == 0){
            plot_bitmap_32(base, oil.posY, oil.posX, 32, oil_unlitBM);
        }
        else {
            plot_bitmap_32(base, oil.posY, oil.posX, 32, oil_litBM);
        }
    } 
}