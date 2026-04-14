#include "ihand.h"

#define MOVE_SPEED 4

extern void quit_game();

void handleAirborneInput(Model *model, int *gameRunning, int jumpVelX) {

    if (has_input()) {
        char input_val = get_input(); /* Read the first queued key to start draining */
        /* Drain every remaining key so the queue stays empty; only the last value is kept, though it is not used while airborne. */
        while (has_input()) {
            input_val = get_input();
        }
         if (input_val == 'q') {
            *gameRunning = 0; /* Allow quitting while airborne */
            quit_game();
        }
    }
    /* Preserve the horizontal velocity set at jump time — no mid-air steering */
    model->mario.deltX = jumpVelX;
}


void handleMoveLeft(Model *model, int *lastGroundDeltX, int *moveBufferFrames) {

    model->mario.deltX = -MOVE_SPEED; 
    model->mario.direction = 0;           
    model->mario.state = 1;
    model->mario.walkFrame = 1 - model->mario.walkFrame;
    *lastGroundDeltX = -MOVE_SPEED; /* Save velocity and reset buffer so a jump this frame carries momentum */  
    *moveBufferFrames = 1;
}

void handleMoveRight(Model *model, int *lastGroundDeltX, int *moveBufferFrames) {

    model->mario.deltX = MOVE_SPEED; 
    model->mario.direction = 1;          
    model->mario.state = 1;          
    model->mario.walkFrame = 1 - model->mario.walkFrame;
    *lastGroundDeltX = MOVE_SPEED; /* Save velocity and reset buffer so a jump this frame carries momentum */
    *moveBufferFrames = 1;
}


void handleClimbUp(Model *model, int *lastGroundDeltX, int *moveBufferFrames) {

    /* Wipe any stored horizontal motion before engaging the ladder */
    *lastGroundDeltX = 0;
    *moveBufferFrames = 0;

    if (model->mario.collideLadder == 1) {

        model->mario.posX = model->ladders[model->mario.ladderIndex].leftB;
        model->mario.climbing = 1;
        model->mario.climbDir = -1;
        model->mario.posY -= 3;
        model->mario.state = 2;        
        model->mario.onGround = 0;
    }
}

void handleClimbDown(Model *model, int *lastGroundDeltX, int *moveBufferFrames) {

    /* Wipe any stored horizontal motion before engaging the ladder */
    *lastGroundDeltX = 0;
    *moveBufferFrames = 0;

    if (model->mario.collideLadder == 1) {
        model->mario.state = 2;       
        model->mario.onGround = 0; 
    }
}


void handleJump(Model *model, int *jumpVelX, int *lastGroundDeltX, int *moveBufferFrames) {

    if (*moveBufferFrames > 0) {
        *jumpVelX = *lastGroundDeltX;
    } else {
        *jumpVelX = 0;  /* No recent horizontal input — jump straight up */
    }

    requestJump(&model->mario);
    model->mario.state = 3;
    model->mario.deltX = *jumpVelX;   /* Apply computed horizontal component */

    /* Prevent stale ground movement from affecting the next landing */
    *lastGroundDeltX = 0;
    *moveBufferFrames = 0;
}

void handleNoGroundInput(Model *model, int *lastGroundDeltX, int *moveBufferFrames) {

    model->mario.deltX = 0; /* No key held — stop sliding */

    if (*moveBufferFrames > 0)
        (*moveBufferFrames)--; /* Count down the grace window */

    /* Once the buffer has fully expired, discard the last movement direction */
    if (*moveBufferFrames == 0)
        *lastGroundDeltX = 0;
}


void inputHandler(Model *model, int *gameRunning) {

    char input_val; /* Holds the most recent key drained from the input queue */

    /* Static variables persist across frames without being global */
    static int jumpVelX = 0; /* Horizontal speed inherited by current jump */
    static int lastGroundDeltX = 0; /* Left/right velocity from the last ground frame */
    static int moveBufferFrames = 0;/* Frames remaining in the jump-momentum grace window */

    /* -------------------------------------------------------------------------
     * Landing reset: the moment Mario touches ground, return him to idle state
     * and wipe airborne velocity so he does not slide after landing.
     * ------------------------------------------------------------------------- */
    if (model->mario.onGround && !model->mario.climbing) {
        model->mario.state = 0; /* Idle / standing state */
        model->mario.deltX = 0; /* Kill any leftover horizontal drift */
        jumpVelX = 0; /* Clear jump velocity — no longer relevant */
    }

    /* Airborne branch: Mario is in the air and not on a ladder.
    Input is drained (to keep the queue clean) but not acted upon.
    Horizontal velocity was fixed at jump time and cannot change mid-air.
    */
    if (!model->mario.onGround && !model->mario.climbing) {
        handleAirborneInput(model, gameRunning, jumpVelX);
        return; /* Nothing else to do this frame */
    }

    /*  No-input branch: Mario is grounded or on a ladder but no key was pressed.
    Tick down the move buffer so jump-momentum eventually expires.
    */
    if (!has_input()) {
        handleNoGroundInput(model, &lastGroundDeltX, &moveBufferFrames);
        return;
    }
    /* Drain the input queue, keeping only the most recently pressed key. This prevents queued-up inputs from producing multiple actions in one
    frame (e.g. the player tapping several keys quickly). */
    input_val = get_input(); /* Read the first key in the queue */
    while (has_input()) input_val = get_input(); /* Overwrite with each newer key; last one wins */

    if (input_val == 'a')
        handleMoveLeft (model, &lastGroundDeltX, &moveBufferFrames);
    else if (input_val == 'd')
        handleMoveRight(model, &lastGroundDeltX, &moveBufferFrames);
    else if (input_val == 'w') 
        handleClimbUp  (model, &lastGroundDeltX, &moveBufferFrames);
    else if (input_val == 's') 
        handleClimbDown(model, &lastGroundDeltX, &moveBufferFrames);
    else if (input_val == ' ') 
        handleJump(model, &jumpVelX, &lastGroundDeltX, &moveBufferFrames);
    else if (input_val == 'q'){
        *gameRunning = 0;
        quit_game(); 
    }
    else                       
        handleNoGroundInput(model, &lastGroundDeltX, &moveBufferFrames); /* Unrecognised key; no input */
}