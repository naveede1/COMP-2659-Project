#include "asynch.h"
#include "mario.h"
#include "input.c"

/* Adjust as Needed */
#define H_MOVE_SPEED 1  
#define V_MOVE_SPEED 1
#define JUMP_FORCE -10

int handle_asynch_events(Model *model) { /* Returns 1 if the Q key pressed (Quit) */

    if (has_input()) {

        char input_char;
        input_char = get_input();

        if (checkQuit(model, input_char)) {
            return 1; /* Return that an Exit was requested */
        }

        if (!checkHorizontal(model, input_char)) {
            if (!checkVertical(model, input_char)) {
                if(!checkJump(model, input_char)) {
                    /* If no valid input recieved, do nothing */
                }
            } 
        }   
    }

    return 0;
}

int checkHorizontal(Model *model, char input_char) { /* Return 1 if Input Used (For Doing Nothing Check)*/

    if (input_char == 'a') {
        if(model->mario.climbing == 0) { /* Only Left if Mario NOT Climbing */
            /* Move Left */
            model->mario.deltX = -H_MOVE_SPEED;
            model->mario.direction = 0;
            model->mario.state = 1;

            /* Animation Handling */
            if (model->mario.walkFrame == 0){
                model->mario.walkFrame = 1;
            } else {
                model->mario.walkFrame = 0;
            }
            return 1;
        }

    } else if (input_char == 'd') {
        if(model->mario.climbing == 0) { /* Only Right if Mario NOT Climbing */
            /* Move Right */
            model->mario.deltX = H_MOVE_SPEED;
            model->mario.direction = 1;
            model->mario.state = 1;
                
            /* Animation Handling */
            if (model->mario.walkFrame == 0){
                model->mario.walkFrame = 1;
            } else {
                model->mario.walkFrame = 0;
            }
            return 1;
        }
    }
    return 0;
}

int checkVertical(Model *model, char input_char) { /* Return 1 if Input Used (For Doing Nothing Check)*/

    if (input_char == 'w') {
        /* Climb Up Ladder */
        if (model->mario.collideLadder == 1) {
            model->mario.deltY = -V_MOVE_SPEED; /* Remember Negative V is UP */
            model->mario.climbing = 1;
            model->mario.state = 2;
        }
        /* Animation Handling */
        if (model->mario.climbFrame == 0){
            model->mario.climbFrame = 1;
        } else {
            model->mario.climbFrame = 0;
        }
        return 1;

    } else if (input_char == 'd') {
        /* Climb Down Ladder */
        if (model->mario.collideLadder == 1 && model->mario.onGround != 0) {
            model->mario.deltY = -V_MOVE_SPEED; /* Remember Negative V is UP */
            model->mario.climbing = 1;
            model->mario.state = 2;
        }
        /* Animation Handling */
        if (model->mario.climbFrame == 0){
            model->mario.climbFrame = 1;
        } else {
            model->mario.climbFrame = 0;
        }
        return 1;
    }

    return 0;
}

int checkJump (Model *model, char input_char) {

    if (input_char == ' ') {
        
        /* Jump (Cannot jump while hammer is active) */
        if (model->mario.onGround == 1 && model->mario.hammerActive == 1) {  
            model->mario.deltY = JUMP_FORCE;
            model->mario.onGround = 0;
            model->mario.state = 3;
        }

        return 1;
    }
    
    return 0;
}

int checkQuit (Model *model, char input_char) {

    if (input_char == 'q') {

        return 1; /* Exit requested */
    }

    return 0;
}