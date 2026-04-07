#include "mario.h"
#include "girder.h"
#include "ladder.h"

#define GRAVITY 1
#define JUMP_FORCE -6
#define MOVE_SPEED 4
#define MAX_FALL_SPEED 10

/* Hammer Animation Timers */
#define HAMMER_DURATION 40
#define HAMMER_FRAME_TIME 1
#define HAMMER_TOTAL_FRAMES 2


void applyGravity(Mario *jm)
{
    if (jm->climbing) {
        jm->deltY = 0; /* no gravity while on a ladder */
        return;
    }

    if (!jm->onGround) {
        jm->deltY += GRAVITY; /* accelerate downward */

        if (jm->deltY > MAX_FALL_SPEED)
            jm->deltY = MAX_FALL_SPEED; /* cap fall speed */
    }
}

void updateMario(Mario *jm, Girder girders[], int numGirders, Ladder ladders[], int numLadders) {
    
    if (jm->climbing) {
        updateClimbing(jm, ladders, numLadders);
    } else {
        applyGravity(jm);
        jm->posX += jm->deltX; /* apply horizontal movement */
        jm->posY += jm->deltY; /* apply vertical movement */
        jm->deltX = 0; /* horizontal speed resets each frame, input must be re-applied next frame */
        resolveGirderCollision(jm, girders, numGirders);
    }
    
    updateHammer(jm);
}

void resolveGirderCollision(Mario *jm, Girder girders[], int numGirders) {
    int i, landingHeight;
    int marioCenterX = jm->posX + 8;  /* horizontal center of Mario */
    int marioFeetY = jm->posY + 15; /* bottom edge of Mario */
    int bestHeight = 32000; /* tracks closest surface found */
    int bestIndex = -1;

    jm->onGround = 0; /* assume airborne until a girder is found */

    for (i = 0; i < numGirders; i++) {

        if (!girders[i].visible)
            continue;

        /* skip girders Mario is not horizontally over */
        if (!isOnGirder(&girders[i], marioCenterX))
            continue;

        /* get the surface height at Mario's horizontal position */
        landingHeight = getGirderHeight(&girders[i], marioCenterX);

        if (landingHeight == -1)
            continue;

        /* only land on girders Mario is falling onto from above*/
        if (jm->deltY >= 0 &&
            marioFeetY >= landingHeight - 2 &&
            marioFeetY <= landingHeight + MAX_FALL_SPEED + 1) {
            /* keep the girder whose surface is closest to Mario's feet */
            if (landingHeight < bestHeight) {
                bestHeight = landingHeight;
                bestIndex  = i;
            }
        }
    }

    /* snap Mario to the closest girder surface found */
    if (bestIndex != -1) {
        jm->posY = bestHeight - 15; /* place feet on surface */
        jm->deltY = 0; /* stop falling */
        jm->onGround = 1; /* mark as grounded */
    }
}

void updateClimbing(Mario *jm, Ladder ladders[], int numLadders) {
    int index;
    int onLadder = 0;
    int marioCenterX = jm->posX + 8;

    for (index = 0; index < numLadders; index++) {
        Ladder *ladder = &ladders[index];

        if (!ladder->visible || ladder->broken)
            continue;

        /* check Mario is horizontally aligned with this ladder */
        if (marioCenterX >= ladder->posX - 5 &&
            marioCenterX <= ladder->posX + 5 &&
            jm->posY >= ladder->topB &&
            jm->posY <= ladder->bottomB) {

            jm->posX = ladder->posX - 8; /* centre Mario on ladder  */
            jm->posY += jm->climbDir * 2; /* move up or down 2px */
            jm->deltY = 0; /* cancel gravity */
            jm->onGround = 0; /* not on ground */
            onLadder = 1;
            break;
        }
    }

    if (!onLadder)
        jm->climbing = 0; /* no ladder found, stop climbing */
}

void updateHammer(Mario *jm) {
    
    if (jm->hammerActive) { /* Main Hammer timer/logic */
    
        jm->hammerTimer++;
        jm->hammerFrameTimer++;

        /* End hammer after duration */
        if (jm->hammerTimer >= HAMMER_DURATION) {

            jm->hammerActive = 0;
            jm->hammerTimer = 0;
            jm->hammerFrame = 0;
            jm->hammerHitActive = 0;
            return;
        
        }

        /* Advance animation frame */
        if (jm->hammerFrameTimer >= HAMMER_FRAME_TIME) {
            jm->hammerFrame++;
            jm->hammerFrameTimer = 0;
            if (jm->hammerFrame >= HAMMER_TOTAL_FRAMES)
                jm->hammerFrame = 0;
        }

        if (jm->hammerActive) { /* Prevents climbing */
        
            if (jm->state == 2)
                jm->state = 0;

        }
    }
}

void requestClimbUp(Mario *jm) {
    jm->climbing = 1;
    jm->climbDir = -1; /* negative Y = upward on screen */
}


void requestClimbDown(Mario *jm) {
    jm->climbing = 1;
    jm->climbDir = 1; /* positive Y = downward on screen */
}

void requestJump(Mario *jm) {
    if (!jm->onGround)
        return; /* cannot jump while airborne or climbing */

    jm->deltY = JUMP_FORCE; /* launch upward */
    jm->onGround = 0; /* no longer grounded */
    jm->state = 3; /* state 3 = jumping */
}

void updateMCollision(Mario *mario) {

    mario->leftB = mario->posX;
    mario->rightB = mario->posX + 16;
    mario->topB = mario->posY;
    mario->bottomB = mario->posY + 16;

}

int checkMCollision(int jmXleftold, int jmYtop, int otherXleft, int otherYtop, int otherXsize, int otherYsize) { /* Returns 1 if the Object Collides with Mario, 0 if not*/

    /* Set Marios Collider */
    int jmXleft = jmXleftold + 2;
    int jmXright = jmXleft + 11;
    int jmYbottom = jmYtop + 15;

    /* Set Other Objects Collider */
    int otherXright = otherXleft + (otherXsize - 1);
    int otherYbottom = otherYtop + (otherYsize - 1);
    
    
    if (jmXleft > otherXleft && jmXleft < otherXright || jmXright > otherXleft && jmXright < otherXright) {
        if (jmYtop < otherYbottom && jmYtop > otherYtop || jmYbottom < otherYbottom && jmYbottom > otherYtop) {
            return 1;
        }
    }
    else {
        return 0;   
    }
}
