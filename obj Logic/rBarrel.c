#include "rBarrel.h"

void renderBarrel(Barrel barrel, UINT16 *base) {

    if (barrel.visible == 1){
        int currPosX = barrel.posX;
        int currPosY = barrel.posY;

        if (barrel.state == 1){
            plot_bitmap_16(base, currPosX, currPosY, 16, barrel_downBM);
        }
        else {
            plot_bitmap_16(base, currPosX, currPosY, 16, barrel_sidewaysBM);
        }
    }
}