#include "rDK.h"

void renderDK(Kong kong, UINT32 *base) {

    if (kong.visible == 1){
       
        int currState = kong.state;

        if (currState == 0) {
            plot_bitmap_32(base, 110, 198, 32, kong_idleLBM);
            plot_bitmap_32(base, 110, 230, 32, kong_idleRBM); 
        }
        else if (currState == 1) {
            plot_bitmap_32(base, 110, 198, 32, kong_grabLBM);
            plot_bitmap_32(base, 110, 230, 32, kong_grabRBM); 
        }
        else if (currState == 2) {
            plot_bitmap_32(base, 110, 198, 32, kong_holdLBM);
            plot_bitmap_32(base, 110, 230, 32, kong_holdRBM); 
        }
        else if (currState == 3) {
            plot_bitmap_32(base, 110, 198, 32, kong_throwLBM);
            plot_bitmap_32(base, 110, 230, 32, kong_throwRBM); 
        }
        else {
            plot_bitmap_32(base, 110, 198, 32, kong_mockLBM);
            plot_bitmap_32(base, 110, 230, 32, kong_mockRBM);
 
        }
    }
} 