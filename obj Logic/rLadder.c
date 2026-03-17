#include "rLadder.h"

void renderLadder(Ladder ladder, UINT32 base) {

    
        
    if (ladder.visible == 1) {
            
        int currPosX = ladder.posX;
        int currPosY = ladder.posY;
        int i;
        int j;
        int k;        
            
        if (ladder.broken == 1) {
            for (i = 0; i < ladder.topSize; i++) {
                plot_bitmap_8(base, currPosX, currPosY, 8, ladder_BM);
                currPosX += 8;
            }
            for (j = 0; j < ladder.skipped; j++) {
                currPosX += 8;
            }
            for (i = 0; i < ladder.bottomSize; i++) {
                plot_bitmap_8(base, currPosX, currPosY, 8, ladder_BM);
                currPosX += 8;
            }
        } else {
            for (i = 0; i < ladder.size; i++) {
                plot_bitmap_8(base, currPosX, currPosY, 8, ladder_BM);
                currPosX += 8;
            }
        }
    }
}

