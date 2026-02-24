#ifndef GIRDER_H
#define GIRDER_H

typedef struct { /* Structure for the Girders */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int left, right; /* Allows for the customizing of size */
    int topLeft, topRight; /* Allows for the drawing of a collider line (Makes it a platform for Jumpman, Barrels and Spirit) */

} Girder;

int isOnGirder(Girder *g, int x);
int getGirderHeight(Girder *g, int x);

#endif