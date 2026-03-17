#include "rLives.h"

void renderLives(Lives lives, UINT32 base) {

    int currPosX = lives.posX;
    int i;

    if (lives.visible == 1){
        for (i = 0; i < lives.count; i++) {

            plot_bitmap_8(base, lives.posY, currPosX, 8, lives_BM);
            currPosX += 10;
        }
    } 
}