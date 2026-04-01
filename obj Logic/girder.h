#ifndef GIRDER_H
#define GIRDER_H

typedef struct { /* Structure for the Girders */

    int visible; /* No = 0, Yes = 1 */
    int posY, posX; /* Current Position of Top-Most Piece*/
    int type; /* Flat = 0, / = 1, \ = 2 */
    int size; /* How many piece make it up */
    int colLeft, colRight; /* Allows for the drawing of a collider line (Makes it a platform for Jumpman, Barrels and Spirit) */

} Girder;

/* ----- Function: getGirderHeight -----

 PURPOSE:  Returns the screen Y of the girder at screen X. 

 INPUT: Girder *g: pointer to the girder struct
        int x: the x coordinate to check

 OUTPUT: The height of the girder at the given x coordinate, or -1 if not visible or out of bounds.
 */

int getGirderHeight(Girder *g, int x); 

/* ----- Function: isOnGirder -----

 PURPOSE:  Returns whether the given x coordinate is within the horizontal bounds of the girder. 
 

 INPUT: Girder *g: pointer to the girder struct
        int x: the x coordinate to check

 OUTPUT: 1 if the x coordinate is within the horizontal bounds of the girder and it is visible, 0 otherwise.
 
 */


int isOnGirder(Girder *g, int x);

#endif