#include "mario.h"
#include "girder.h"
#include "ladder.h"
#include <stdio.h>

/* Gravity Function */
void applyGravity(Mario *jm)
{
    if (jm->climbing) {
        jm->deltY = 0;
        return;
    }

    if (!jm->onGround) {
        jm->deltY += GRAVITY;

        if (jm->deltY > MAX_FALL_SPEED) {
            jm->deltY = MAX_FALL_SPEED;
        }
    }
}

void updateMario(Mario *jm, Girder girders[], int numGirders,
                 Ladder ladders[], int numLadders)
{
    if (jm->climbing) {
        updateClimbing(jm, ladders, numLadders);
    } else {
        applyGravity(jm);
        jm->posX += jm->deltX;
        jm->posY += jm->deltY;
        jm->deltX = 0;
        resolveGirderCollision(jm, girders, numGirders);
    }
    updateHammer(jm);
}

void snapMarioToNearestGirder(Mario *jm, Girder girders[], int numGirders)
{
    int i;
    int bestIndex = -1;
    int bestHeight = 10000;
    int marioCenterX = jm->posX + 8;

    for (i = 0; i < numGirders; i++)
    {
        int height;

        if (!girders[i].visible)
            continue;

        if (!isOnGirder(&girders[i], marioCenterX))
            continue;

        height = getGirderHeight(&girders[i], marioCenterX);

        if (height == -1)
            continue;

        if (height >= jm->posY && height < bestHeight) {
            bestHeight = height;
            bestIndex = i;
        }
    }

    if (bestIndex != -1) {
        jm->posY = bestHeight - 15;
        jm->deltY = 0;
        jm->onGround = 1;
    }
}

void resolveGirderCollision(Mario *jm, Girder girders[], int numGirders)
{
    int i;
    int marioCenterX = jm->posX + 8;  /* horizontal center */
    int marioFeetY   = jm->posY + 15; /* vertical bottom   */

    jm->onGround = 0;

    for (i = 0; i < numGirders; i++)
    {
        int landingHeight;

        if (!girders[i].visible)
            continue;

        if (!isOnGirder(&girders[i], marioCenterX))
            continue;

        landingHeight = getGirderHeight(&girders[i], marioCenterX);

        if (landingHeight == -1)
            continue;

        if (jm->deltY >= 0 &&
            marioFeetY >= landingHeight - 2 &&
            marioFeetY <= landingHeight + MAX_FALL_SPEED + 1)
        {
            jm->posY     = landingHeight - 15;
            jm->deltY    = 0;
            jm->onGround = 1;
            break;
        }
    }
}

void updateClimbing(Mario *jm, Ladder ladders[], int numLadders)
{
    int i;
    int onLadder;
    int marioCenterX;

    onLadder = 0;
    marioCenterX = jm->posX + 8;

    for (i = 0; i < numLadders; i++)
    {
        Ladder *ladder = &ladders[i];

        if (!ladder->visible || ladder->broken)
            continue;

        if (marioCenterX >= ladder->posX - 5 &&
            marioCenterX <= ladder->posX + 5 &&
            jm->posY >= ladder->topB &&
            jm->posY <= ladder->bottomB)
        {
            jm->posX = ladder->posX - 8;
            jm->posY += jm->climbDir * 2;
            jm->deltY = 0;
            jm->onGround = 0;
            onLadder = 1;
            break;
        }
    }

    if (!onLadder)
        jm->climbing = 0;
}

void updateHammer(Mario *jm)
{
    if (!jm->hammerActive)
        return;

    jm->hammerTimer++;
    jm->hammerFrameTimer++;

    if (jm->hammerTimer >= HAMMER_DURATION)
    {
        jm->hammerActive = 0;
        jm->hammerTimer = 0;
        jm->hammerFrame = 0;
        jm->hammerHitActive = 0;
        return;
    }

    if (jm->hammerFrameTimer >= HAMMER_FRAME_TIME)
    {
        jm->hammerFrame++;
        jm->hammerFrameTimer = 0;

        if (jm->hammerFrame >= HAMMER_TOTAL_FRAMES)
            jm->hammerFrame = 0;
    }

    jm->hammerHitActive = (jm->hammerFrame == 1 || jm->hammerFrame == 3) ? 1 : 0;

    if (jm->state == 2)
        jm->state = 0;
}

void requestClimbUp(Mario *jm)
{
    jm->climbing = 1;
    jm->climbDir = -1;
}

void requestClimbDown(Mario *jm)
{
    jm->climbing = 1;
    jm->climbDir = 1;
}
