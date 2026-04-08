#ifndef IHAND_H
#define IHAND_H

#include "model.h"

/*----- Function: handleAirborneInput -----

 PURPOSE: Called every frame while Mario is airborne (not on ground, not
          climbing). Drains the input queue so it does not back up, but
          ignores all key presses. Horizontal velocity is locked to whatever
          it was at the moment of the jump.

 INPUT: Model(Model*): pointer to the game model containing all game state
        gameRunning(int*): pointer to the main loop control flag
        jumpVelX(int): horizontal velocity locked in at jump time

 OUTPUT: None

*/

void handleAirborneInput(Model *model, int *gameRunning, int jumpVelX);

/*----- Function: handleMoveLeft -----

 PURPOSE: Moves Mario one frame to the left along the ground. Updates his
          facing direction, walking state, and animation frame. Records the
          movement so a jump started immediately afterward inherits momentum.

 INPUT: Model(Model*): pointer to the game model containing all game state
        lastGroundDeltX(int*): stores the most recent horizontal ground velocity
        moveBufferFrames(int*): reset to 1, keeping the momentum window open

 OUTPUT: None

*/

void handleMoveLeft(Model *model, int *lastGroundDeltX, int *moveBufferFrames);

/*----- Function: handleMoveRight -----

 PURPOSE: Moves Mario one frame to the right along the ground. Mirror of
          handleMoveLeft — same logic with positive (rightward) velocity
          and direction flag set to 1.

 INPUT: Model(Model*): pointer to the game model containing all game state
        lastGroundDeltX(int*): stores the most recent horizontal ground velocity
        moveBufferFrames(int*): reset to 1, keeping the momentum window open

 OUTPUT: None

*/

void handleMoveRight(Model *model, int *lastGroundDeltX, int *moveBufferFrames);

/*----- Function: handleClimbUp -----

 PURPOSE: Attempts to move Mario upward on a ladder. Only acts if Mario is
          touching a ladder (collideLadder == 1). Clears all horizontal
          momentum before engaging the ladder.

 INPUT: Model(Model*): pointer to the game model containing all game state
        lastGroundDeltX(int*): cleared to prevent stale horizontal momentum
        moveBufferFrames(int*): cleared so no jump momentum lingers

 OUTPUT: None

*/

void handleClimbUp(Model *model, int *lastGroundDeltX, int *moveBufferFrames);

/*----- Function: handleClimbDown -----

 PURPOSE: Attempts to move Mario downward on a ladder. Only acts if Mario is
          touching a ladder (collideLadder == 1). Clears all horizontal
          momentum before engaging the ladder.

 INPUT: Model(Model*): pointer to the game model containing all game state
        lastGroundDeltX(int*): cleared to prevent stale horizontal momentum
        moveBufferFrames(int*): cleared so no jump momentum lingers

 OUTPUT: None

*/

void handleClimbDown(Model *model, int *lastGroundDeltX, int *moveBufferFrames);

/*----- Function: handleJump -----

 PURPOSE: Initiates a jump. If a directional key was pressed recently
          (move buffer active), the last ground velocity is carried into
          the jump arc. Otherwise Mario jumps straight up. Clears all
          ground movement state after launching.

 INPUT: Model(Model*): pointer to the game model containing all game state
        jumpVelX(int*): set to the horizontal velocity to carry through the jump
        lastGroundDeltX(int*): provides momentum if buffer active; cleared after jump
        moveBufferFrames(int*): checked for remaining frames; cleared after jump

 OUTPUT: None

*/

void handleJump(Model *model, int *jumpVelX, int *lastGroundDeltX, int *moveBufferFrames);

/*----- Function: handleNoGroundInput -----

 PURPOSE: Handles idle or unrecognised input while Mario is grounded. Stops
          horizontal movement immediately and ticks down the jump-momentum
          grace window. Once the window expires, the stored last-direction
          is also cleared.

 INPUT: Model(Model*): pointer to the game model containing all game state
        lastGroundDeltX(int*): zeroed once the move buffer expires
        moveBufferFrames(int*): decremented each idle frame; clamped at 0

 OUTPUT: None

*/

void handleNoGroundInput(Model *model, int *lastGroundDeltX, int *moveBufferFrames);

/*----- Function: inputHandler -----

 PURPOSE: Top-level input dispatcher, called once per game frame. Resets
          Mario to idle on landing, delegates to handleAirborneInput when
          in the air, then drains the input queue and routes the most recent
          key to the appropriate sub-handler when grounded or climbing.

          Key bindings:
            a     - move left
            d     - move right
            w     - climb up
            s     - climb down
            space - jump (inherits momentum if pressed shortly after moving)
            q     - quit the game

 INPUT: Model(Model*): pointer to the game model struct holding all game
                       state, including Mario's position, velocity, animation
                       frames, and collision flags
        gameRunning(int*): pointer to the main loop control flag; set to 0 to exit

 OUTPUT: None

*/

void inputHandler(Model *model, int *gameRunning);

#endif