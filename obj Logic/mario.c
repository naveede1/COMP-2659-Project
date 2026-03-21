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
    best_distance = 400;

    mario_left_edge = mario->posX;
    mario_right_edge = mario->posX + mario->width;
    mario_bottom_edge = mario->posY + mario->height;

    printf("Mario left: %d, right: %d, bottom: %d\n", mario_left_edge, mario_right_edge, mario_bottom_edge);
    printf("Mario width: %d, height: %d\n", mario->width, mario->height);

    /* Checking each girder rendered */
    for (i = 0; i < 9; i++) {
        /* Check if Mario is within the horizontal range of the girder */
        girder_left_edge = girders[i].posY;
        girder_right_edge = girders[i].posY + (girders[i].size * girders[i].width);
        girder_top_edge = girders[i].posX;

        printf("Girder %d - left: %d, right: %d, top: %d\n", i, girder_left_edge, girder_right_edge, girder_top_edge);

        if ((mario_left_edge >= girder_left_edge) && (mario_right_edge <= girder_right_edge)) {
            printf("Horizontal check passed for girder %d\n", i);
            printf("girder_top_edge: %d, mario_bottom_edge: %d\n", girder_top_edge, mario_bottom_edge);
            /* Check if Mario is above a girder */
            if (girder_top_edge <= mario_bottom_edge) {
                printf("Vertical check passed for girder %d\n", i);
                distance = mario_bottom_edge - girder_top_edge;
                printf("distance: %d, best_distance: %d\n", distance, best_distance);
                if (distance < best_distance) {
                    best_distance = distance;
                    correct_girder = &girders[i];
                    printf("correct_girder set to girder %d\n", i);
                }
            }
        }
    }

    printf("correct_girder is %s\n", correct_girder == NULL ? "NULL" : "SET");
    if (correct_girder == NULL) return FALSE;

    /* Snapping Mario to the slope of the girder */
    girder_top_edge = correct_girder->posX;
    mario->posY = girder_top_edge - mario->height;
    
    printf("correct_girder is %s\n", correct_girder == NULL ? "NULL" : "SET");
    return TRUE;
    
}

void apply_gravity_mario(Mario *mario) {

}