#ifndef MARIO_H
#define MARIO_H

#include "girder.h"
#include "ladder.h"

typedef struct { /* Structure for Jumpman */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int deltX, deltY; /* Current Horizontal/Veritcal Velocity */ 
    int state; /* Standing = 0, Walking = 1, Climbing = 2, Jumping = 3, Dead (Falling off screen) = 4 */ 
    int direction; /* Left = 0, Right = 1 */
    int climbing;   /* No = 0, Yes = 1 */
    int climbDir;   /* Up = -1, Down = 1 */
    int collideLadder;   /* No = 0, Yes = 1 */
    int onGround; /* Is JumpMan Grounded? No = 0, Yes = 1 */ 
    int hammerActive; /* No = 0, Yes = 1 */
    int hammerTimer; /* How long Jumpman has left in his Hammer powerup */
    int dead; /* Should I be falling offscreen? No = 0, Yes = 1 */

    int walkFrame;
    int climbFrame;

    /* (The Hammer swinging is a pain but we'll see if this works)*/
    int hammerFrame;        /* current animation frame */
    long hammerFrameTimer; /* time spent in current frame */
    int hammerHitActive;    /* 1 when swing can destroy barrels */

    int leftB, rightB, topB, bottomB; /* Collider Bounds */

} Mario;

/*------ Function: requestClimbUp -----

PURPOSE: Sets Mario's climbing state to climbing and climb direction to up. Called when the player presses the climb up key.

INPUT: Mario *jm: Pointer to the Mario struct

OUTPUT: None

 */
void requestClimbUp(Mario *jm);
/* ------ Function: requestClimbDown -----

PURPOSE: Sets Mario's climbing state to climbing and climb direction to down. Called when the player presses the climb down key.

  INPUT: Mario *jm: Pointer to the Mario struct
 
  OUTPUT: None
 */
void requestClimbDown(Mario *jm);

/*------ Function: updateClimbing -----
PURPOSE: Applies gravity to Mario, accelerating him downwards if he is not on the ground

INPUT: Mario *jm: Pointer to the Mario struct
         Ladder ladders[]: Array of ladder structs
         int numLadders: Number of ladders in the array

OUTPUT: None
 */

void updateClimbing(Mario *jm, Ladder ladders[], int numLadders);

/* ------ Function: applyGravity -----

PURPOSE: Applies gravity to Mario, accelerating him downwards if he is not on the ground

INPUT: Mario *jm: Pointer to the Mario struct

OUTPUT: None
 
*/

void applyGravity(Mario *jm);


void updateHammer(Mario *jm);

/*----- Function: updateMario -----

PURPOSE: Updates Mario's position and state based on his velocity, gravity, and collisions with girders and ladders. Should be called once per frame.

INPUT: Mario *jm: Pointer to the Mario struct
    Girder girders[]: Array of girder structs
    int numGirders: Number of girders in the array
    Ladder ladders[]: Array of ladder structs
    int numLadders: Number of ladders in the array

OUTPUT: None

*/
void updateMario(Mario *jm, Girder girders[], int numGirders, Ladder ladders[], int numLadders);

/*----- Function: resolveGirderCollision -----

PURPOSE: Resolves collision between Mario and a girder.

INPUT: Mario *jm: Pointer to the Mario struct
    Girder girders[]: Array of girder structs
    int numGirders: Number of girders in the array

OUTPUT: None
*/
void resolveGirderCollision(Mario *jm, Girder girders[], int numGirders);

void updateMCollision(Mario *mario);

int checkMCollision(int jmXleft, int jmYtop, int otherXleft, int otherYtop, int otherXsize, int otherYsize);

#endif