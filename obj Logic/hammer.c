#include "hammer.h"
#include "mario.h"

void checkHammer(Mario *mario, Hammer hammers[]) { /* Changes the states for the Synchronous Check */
 
    int hamNum;
    
    for (hamNum = 0; hamNum < 2; hamNum++) {
    
        if(checkMCollision(mario->posX, mario->posY, hammers[hamNum].posX, hammers[hamNum].posY, 16)) {

            hammers[hamNum].visible = 0;
            mario->hammerActive = 1;
            mario->hammerTimer = 0;
            mario->hammerFrameTimer = 0;
            return;
        }
    }
}
