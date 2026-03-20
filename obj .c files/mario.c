#include <stdio.h>
#include "mario.h"
#include "girder.h"
#include "ladder.h"

boolean is_mario_grounded(Mario *mario, Model *model) {

    /*
    
    Cycling through all the girders rendered:

        First check: Is the girder horizontally within the range of Mario?
        Second check: Is the girder below Mario's feet?

        Which ever girders that fit these descriptions will be considered a candidate will
        be added to a list

        Choose the girder with the smallest posY difference from Mario to the girder

        Once we have the right girder, we check if for if Mario is grounded

    */

    Girder *correct_girder; 
    int best_distance;
    int distance; /* posY difference */

    int mario_left_edge, mario_right_edge;
    int mario_bottom_edge; /* posY of Mario's Feet */

    int girder_left_edge, girder_right_edge, girder_top_edge;

    int i;

    correct_girder = NULL;
    best_distance = 100000;

    mario_left_edge = mario->posX;
    mario_right_edge = mario->posX + mario->width;
    mario_bottom_edge = mario->posY + mario->height;

    /* Checking each girder rendered */
    for (i = 0; i < 9; i++) {
        /* Check if Mario is within the horizontal range of the girder */
        girder_left_edge = model->girders[i].posX;
        girder_right_edge = model->girders[i].posX + model->girders[i].width;

        if ((mario_left_edge >= girder_left_edge) && (mario_right_edge <= girder_right_edge)) {
            /* Check if Mario is above a girder */
            girder_top_edge = model->girders[i].posY;
            if (mario_bottom_edge >= girder_top_edge) {
                distance = girder_top_edge - mario_bottom_edge;
                if (distance < best_distance) {
                    best_distance = distance;
                    correct_girder = &model->girders[i];
                }
            }
        }
    }

    if (correct_girder == NULL) return FALSE;

    /* Snapping Mario to the slope of the girder */
    girder_top_edge = correct_girder->posY;
    mario->posY = girder_top_edge - mario->height;
    
    return TRUE;
    
}

void apply_gravity_mario(Mario *mario) {

}

/* Gravity Function */

void applyGravity(Mario *jm) {
    jm->deltY += GRAVITY;
}

/* Frame Update (Movement/Frame) */

void updateMario(Mario *jm, Girder girders[], int numGirders, Ladder ladders[], int numLadders, float deltaTime) {
    
    applyGravity(jm);

    jm->posX += jm->deltX;
    jm->posY += jm->deltY;

    jm->deltX = 0; /* Resets the horizontal speed each frame */

    int onPlatform = 0;

    for (int i = 0; i < numGirders; i++) /* Ensures Mario doesn't fall through Girders */
    {
        if (isOnGirder(&girders[i], jm->posX))
        {
            int height = getGirderHeight(&girders[i], jm->posX);

            if (jm->posY >= height)
            {
                jm->posY = height;
                jm->deltY = 0;
                jm->onGround = 1;
                onPlatform = 1;
            }
        }
    }

    if (!onPlatform) { /* For Gravity to work properly */
        
        jm->onGround = 0;

    }

    if (jm->hammerActive) { /* Main Hammer timer/logic */
    
        jm->hammerTimer += deltaTime;
        jm->hammerFrameTimer += deltaTime;

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

        /* Activate hit frames (This is what the actual arcade does, only attacks frame 1 and 3 of animation) */
        if (jm->hammerFrame == 1 || jm->hammerFrame == 3) { 

            jm->hammerHitActive = 1;
        
        } else {

            jm->hammerHitActive = 0;
            
        }

        if (jm->hammerActive) { /* Prevents climbing */
        
            if (jm->state == 2)
                jm->state = 0;

        }
    }

    /* Climbing Loop */
    if (jm->climbing)
{
    int onLadder = 0;

   for (int i = 0; i < numLadders; i++)
{
    Ladder *ladder = &ladders[i];

    if (!ladder->visible || ladder->broken)
        continue;

    if (jm->posX >= ladder->posX - 5 &&
        jm->posX <= ladder->posX + 5 &&
        jm->posY >= ladder->top &&
        jm->posY <= ladder->bottom)
    {
        jm->posX = ladder->posX;
        jm->posY += jm->climbDir * 2;
        jm->onGround = 0;
        break;
    }
}

    /* If no ladder found, stop climbing */
    if (!onLadder)
    {
        jm->climbing = 0;
    }
}

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