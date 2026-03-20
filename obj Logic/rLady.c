#include "rLady.h"

void renderLady(Lady lady, UINT32 *base) {
    
    if (lady.visible == 1){
       if (lady.state == 0) {
        plot_bitmap_32(base, lady.posY, lady.posX, 32, lady_idleBM);
       }
       else {
        plot_bitmap_32(base, lady.posY, lady.posX, 32, lady_winBM);
       }
    } 
}