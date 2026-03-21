#include <stdio.h>

#include "mario.h"

boolean is_mario_grounded(Mario *mario, Girder *girders) {

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
    best_distance = 2;

    mario_left_edge = mario->posX;
    mario_right_edge = mario->posX + mario->width;
    mario_bottom_edge = mario->posY + mario->height;

    /* Checking each girder rendered */
    for (i = 0; i < 9; i++) {
        /* Check if Mario is within the horizontal range of the girder */
        girder_left_edge = girders[i].posY;
        girder_right_edge = girders[i].posY + (girders[i].size * girders[i].width);
        girder_top_edge = girders[i].posX;

        if ((girder_top_edge >= mario_bottom_edge - 1) && (girder_top_edge <= mario_bottom_edge + 1)) {
            /* Check if Mario is above a girder */
            printf("Horizontal check passed for girder %d\n", i);
            if (girder_top_edge >= mario_bottom_edge) {
                printf("Vertical check passed for girder %d, distance: %d\n", i, girder_top_edge - mario_bottom_edge);
                distance = girder_top_edge - mario_bottom_edge;
                if (distance < best_distance) {
                    best_distance = distance;
                    correct_girder = &girders[i];
                }
            }
        }
    }

    if (correct_girder != NULL) {
        printf("Selected girder posX: %d, posY: %d, mario_bottom: %d\n", correct_girder->posX, correct_girder->posY, mario_bottom_edge);
    }

    if (correct_girder == NULL) return FALSE;

    printf("correct_girder posX: %d, posY: %d\n", correct_girder->posX, correct_girder->posY);

    /* Snapping Mario to the slope of the girder */
    girder_top_edge = correct_girder->posX;
    if ((girder_top_edge - mario_bottom_edge) <= 1) {
        mario->posY = girder_top_edge - mario->height;
        printf("After snap: mario posY: %d, mario bottom: %d, girder top: %d\n", mario->posY, mario->posY + mario->height, girder_top_edge);
        return TRUE;
    }

    return FALSE;
    
}

void apply_gravity_mario(Mario *mario, Girder *girders) {
    mario->posY++;
    if (is_mario_grounded(mario, girders)) {
        return;
    }
}