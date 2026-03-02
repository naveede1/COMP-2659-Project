#include "rGirder.h"

void renderGirder(Girder girder, UINT32 base) {

    if (girder.visible == 1){
        int currPosX = girder.posX;
        int currPosY = girder.posY;
        int i;

        for (i = 0; i < girder.size; i++) {

            plot_bitmap_8(base, currPosX, currPosY, 8, girder_BM);
            currPosY += 8;
            plot_bitmap_8(base, currPosX, currPosY, 8, girder_BM);

            if (girder.type == 1) {
                currPosX -= 1;
            } else if (girder.type == 2) {
                currPosX += 1;
            }

            currPosY += 8;
        }
    }
}