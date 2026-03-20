#include "rSpirit.h"

void renderSpirit(Spirit spirit, UINT32 *base) {
    
    if (spirit.visible == 1){
       if (spirit.direction == 0) {
        plot_bitmap_16(base, spirit.posY, spirit.posX, 16, spirit_LeftBM);
       }
       else {
        plot_bitmap_16(base, spirit.posY, spirit.posX, 16, spirit_RightBM);
       }
    } 
}