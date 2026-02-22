#ifndef LADDER_H
#define LADDER_H

typedef struct { /* Structure for Ladders */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int broken; /* No = 0, Yes = 1 */
    int top, bottom; /* Vertical Bounds */
    int right, left; /* Horizontal Bounds */
} Ladder;

int isOnLadder(Ladder *ladder, int x, int y);
int canClimb(Ladder *ladder);
int barrelCanDescend(Ladder *ladder);

#endif