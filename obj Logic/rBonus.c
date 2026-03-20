#include "rBonus.h"

void renderBonus(Timer timer, UINT32 *base) {

    if (timer.visible == 1){

        linea0();
        plot_string(base, timer.posY - 4, timer.posX, "BONUS");  
        /*plot_string(base, timer.posY + 15, timer.posX + 4, timer.value);*/

        plot_bitmap_32(base, timer.posY - 2, timer.posX - 4, 32, bonus_leftBM);
        plot_bitmap_32(base, timer.posY - 2, timer.posX + 28, 32, bonus_rightBM);
    }
} 