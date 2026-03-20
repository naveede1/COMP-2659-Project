#ifndef GIRDER_H
#define GIRDER_H

typedef struct { /* Structure for the Girders */

    int visible; /* No = 0, Yes = 1 */
    int posY, posX; /* Current Position of Top-Most Piece*/
    int type; /* Flat = 0, / = 1, \ = 2 */
    int size; /* How many piece make it up */
    int colLeft, colRight; /* Allows for the drawing of a collider line (Makes it a platform for Jumpman, Barrels and Spirit) */

} Girder;

#endif