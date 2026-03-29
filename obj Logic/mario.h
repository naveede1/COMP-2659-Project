#ifndef MARIO_H
#define MARIO_H

#include "girder.h"
#include "ladder.h"

#define GRAVITY 1
#define MAX_FALL_SPEED 10
#define JUMP_FORCE -10
#define MOVE_SPEED 4
#define HAMMER_DURATION 300

/* For Hammer swinging animation 
#define HAMMER_DURATION 8.0f*/
#define HAMMER_FRAME_TIME 10
#define HAMMER_TOTAL_FRAMES 4

typedef struct { /* Structure for Jumpman */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int deltX, deltY; /* Current Horizontal/Veritcal Velocity */ 
    int state; /* Standing = 0, Walking = 1, Climbing = 2, Jumping = 3, Dead (Falling off screen) = 4 */ 
    int direction; /* Left = 0, Right = 1 */
    int climbing;   /* No = 0 , Yes = 1 */
    int climbDir;   /* Up = -1, Down = 1 */
    int collideLadder;   /* No = 0, Yes = 1 */
    int onGround; /* Is JumpMan Grounded? No = 0, Yes = 1 */ 
    int hammerActive; /* No = 0, Yes = 1 */
    long hammerTimer;
    int dead; /* Should I be falling offscreen? No = 0, Yes = 1 */

    int walkFrame;
    int climbFrame;

    /* (The Hammer swinging is a pain but we'll see if this works)*/
    int hammerFrame;        /* current animation frame */
    long hammerFrameTimer; /* time spent in current frame */
    int hammerHitActive;    /* 1 when swing can destroy barrels */

    int leftB, rightB, topB, bottomB; /* Collider Bounds */

} Mario;

void applyGravity(Mario *jm);
void updateMario(Mario *jm, Girder girders[], int numGirders, Ladder ladders[], int numLadders);
void resolveGirderCollision(Mario *jm, Girder girders[], int numGirders);
void updateClimbing(Mario *jm, Ladder ladders[], int numLadders);
void updateHammer(Mario *jm);
void requestClimbUp(Mario *jm);
void requestClimbDown(Mario *jm);

#endif