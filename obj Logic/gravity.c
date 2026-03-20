/*

TO DO:
[X] Move edges(maybe), width and heights to respective .h files 
[X] Gravity for Mario and barrel can be in there .c files
[] Potentially make helper function that takes a single girder and return the displacement
   between Mario and the Girder
[] Types file (No time)
[] Clean up and condense code
[] Rework, I belive grounded function only needs to take the model as a parameter
[] Look into the mario.c files with Aidan
[] Add documentation for gravity functions after completion
[] Have Aiden add documentation to functions being used and remove functions that are not being used

*/

#include <stdio.h>

#include "gravity.h"
#include "mario.h"
#include "girder.h"
#include "model.h"
#include "barrel.h"

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

boolean is_barrel_grounded(Barrel *barrel, Model *model) {
    return FALSE;
}

void apply_gravity_barrel(Barrel barrel) {

}