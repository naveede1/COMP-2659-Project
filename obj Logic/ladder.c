#include "ladder.h"
#include "mario.h"

void checkLadders(Mario *mario, Ladder ladder[]) {

    int ladNum;

    for (ladNum = 0; ladNum < 17; ladNum++) {
        if (ladder[ladNum].broken == 0) { /* Only non-broken ladders are climbable */
            if(checkMCollision(mario->posX, mario->posY, ladder[ladNum].posX, ladder[ladNum].posY, 8, (ladder[ladNum].size * 8))){
                mario->collideLadder = 1;
                return;
            }
        }
    }
    mario->collideLadder = 0;
    return;
}