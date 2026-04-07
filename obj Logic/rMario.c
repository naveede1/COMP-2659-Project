#include "rMario.h"

void renderMario(Mario mario, UINT16 *base) {

    if (mario.visible == 1){

        if (mario.hammerActive == 1) {
            if(mario.direction == 0) {
                renderMHammerLeft(mario, base);
            }
            else {
                renderMHammerRight(mario, base);
            }
        }
        else { 
            if (mario.direction == 0) {
                renderMLeft(mario, base);
            } 
            else {
                renderMRight(mario, base);
            }
        }
    }
}

void renderMHammerLeft(Mario mario, UINT16 *base) {

    if (mario.hammerFrame == 0) {
        plot_bitmap_16(base, mario.posY+2, mario.posX-15, 16, hammer_downLeftBM);
        plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hammerDownLeftBM);

    } else if (mario.hammerFrame == 1) {
        plot_bitmap_16(base, mario.posY-15, mario.posX+2, 16, hammer_upBM);
        plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hammerUpLeftBM);
    }
}

void renderMHammerRight(Mario mario, UINT16 *base) {
                
    if (mario.hammerFrame == 0) {
        plot_bitmap_16(base, mario.posY+2, mario.posX+15, 16, hammer_downRightBM);
        plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hammerDownRightBM);
    } else if (mario.hammerFrame == 1) {
        plot_bitmap_16(base, mario.posY-15, mario.posX-2, 16, hammer_upBM);
        plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hammerUpRightBM);
    }
}

void renderMLeft(Mario mario, UINT16 *base) {

    int currState = mario.state;

    if (currState == 0) {
        plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkInLeftBM);
    } else if (currState == 1) {    
        if (mario.walkFrame == 0) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkInLeftBM);
            mario.walkFrame = 1;
        } else {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkOutLeftBM);
            mario.walkFrame = 0;
        }
    } else if (currState == 2) {
        if (mario.climbFrame == 0) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_climbLeftBM);
            mario.walkFrame = 1;
        } else {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_climbRightBM);
            mario.walkFrame = 0;
        }
    } else if (currState == 3) {
        plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_jumpLeftBM);
    } else {
        if (mario.dead == 1) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_deadBM);
        } else {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hitBM);
        }
    }
}

void renderMRight(Mario mario, UINT16 *base) {
    int currState = mario.state;
    if (currState == 0) {
        plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkInRightBM);
    } else if (currState == 1) {
        if (mario.walkFrame == 0) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkInRightBM);
        } else {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkOutRightBM);
        }
    } else if (currState == 2) {
        if (mario.climbing == 0) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_climbPullBM);
        } else if (mario.climbFrame == 0) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_climbLeftBM);
            mario.walkFrame = 1;
        } else {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_climbRightBM);
            mario.walkFrame = 0;
        }
    } else if (currState == 3) {
        plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_jumpRightBM);
    } else {
        if (mario.dead == 1) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_deadBM);
        } else {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hitBM);
        }
    }
}
