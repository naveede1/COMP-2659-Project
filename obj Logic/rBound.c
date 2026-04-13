#include "rBound.h"

void renderBounds(UINT8 *base) {

    renderVertBounds(base);
    renderHoriBounds(base);
    renderCorners(base);
    
} 

void renderVertBounds(UINT8 *base) {

    int i;
    int currLY = 10; 
    int currRY = 10; 

    for(i = 0; i < 47; i++) { /* Left Side */
        plot_bitmap_8(base, currLY, 168, 8, vBound_LBM);
        currLY += 8;
    }

    for(i = 0; i < 47; i++) { /* Right Side */
        plot_bitmap_8(base, currRY, 400, 8, vBound_RBM);
        currRY += 8;
    }
}

void renderHoriBounds(UINT8 *base) {

    int i;
    int currTX = 176; 
    int currBX = 176;

    for(i = 0; i < 28; i++) { /* Top Side */
        plot_bitmap_8(base, 2, currTX, 8, hBound_TBM);
        currTX += 8;
    }

    for(i = 0; i < 28; i++) { /* Bottom Side */
        plot_bitmap_8(base, 386, currBX, 8, hBound_BBM);
        currBX += 8;
    }

}

void renderCorners(UINT8 *base) {

    plot_bitmap_8(base, 2, 168, 8, TLCorner_BM);
    plot_bitmap_8(base, 2, 400, 8, TRCorner_BM);
    plot_bitmap_8(base, 386, 168, 8, BLCorner_BM);
    plot_bitmap_8(base, 386, 400, 8, BRCorner_BM);

}