#ifndef MARIO_H
#define MARIO_H

#include "girder.h"

#define GRAVITY 0.5f
#define JUMP_FORCE -10
#define MOVE_SPEED 3
#define HAMMER_DURATION 8.0f

/* For Hammer swinging animation */
#define HAMMER_DURATION 8.0f
#define HAMMER_FRAME_TIME 0.15f
#define HAMMER_TOTAL_FRAMES 4

typedef struct { /* Structure for Jumpman */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int deltX, deltY; /* Current Horizontal/Veritcal Velocity */ 
    int state; /* Standing = 0, Walking = 1, Climbing = 2, Jumping = 3, Dead (Falling off screen) = 4 */ 
    int direction; /* Left = 0, Right = 1 */
    int climbing;   /* No = 0, Yes = 1 */
    int climbDir;   /* -1 = up, 1 = down */
    int onGround; /* Is JumpMan Grounded? No = 0, Yes = 1 */ 
    int hammerActive; /* No = 0, Yes = 1 */
    float hammerTimer;
    int dead; /* Should I be falling offscreen? No = 0, Yes = 1 */

    /* (The Hammer swinging is a pain but we'll see if this works)*/
    int hammerFrame;        /* current animation frame */
    float hammerFrameTimer; /* time spent in current frame */
    int hammerHitActive;    /* 1 when swing can destroy barrels */

} Mario;

void moveLeft(Mario *jm);
void moveRight(Mario *jm);
void jump(Mario *jm);
void applyGravity(Mario *jm);
void updateMario(Mario *jm, Girder girders[], int numGirders, Ladder ladders[], int numLadders, float deltaTime);

#endif