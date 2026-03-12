#include "rMario.h"

void renderMario(Mario mario, UINT32 base) {

    if (mario.visible == 1){
       
        int currState = mario.state;

        if (mario.hammerActive == 1) {
            if(mario.direction == 0) {
                plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hammerDownLeftBM);
            }
            else {
                plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hammerUpRightBM);
            }
        }
        else { 
            if (mario.direction == 0) {
                if (currState == 0) {
                    plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkInLeftBM);
                }
                else if (currState == 1) {
                    plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkOutLeftBM);
                }
                else if (currState == 2) {
                    plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_climbLeftBM);
                }
                else if (currState == 3) {
                    plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_jumpLeftBM);
                }
                else {
                    plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hitBM);
                }
            } 
            else {
                if (currState == 0) {
                    plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkInRightBM);
                }
                else if (currState == 1) {
                    plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkOutRightBM);
                }
                else if (currState == 2) {
                    plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_climbRightBM);
                }
                else if (currState == 3) {
                    plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_jumpRightBM);
                }
                else {
                    plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hitBM);
                }
            }
        }
    }
}