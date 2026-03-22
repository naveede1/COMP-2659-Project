#include "rHeart.h"

void renderHeart(Heart heart, UINT16 *base) {
    
    if (heart.visible == 1){
       if (heart.broken == 0) {
        plot_bitmap_16(base, heart.posY, heart.posX, 16, heart_fullBM);
       }
       else {
        plot_bitmap_16(base, heart.posY, heart.posX, 16, heartbrokenBM);
       }
    } 
}