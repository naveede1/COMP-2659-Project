#ifndef LADDER_H
#define LADDER_H

typedef struct { /* Structure for Ladders */

    int visible; /* No = 0, Yes = 1 */
    int posY, posX; /* Current Position */
    int broken; /* No = 0, Yes = 1 */
    int top, bottom; /* Vertical Bounds */
    int right, left; /* Horizontal Bounds */
    
    int size; /* How many rungs make up the ladder */
    int topSize; /* How many rungs are at the top of the Broken Ladder */
    int bottomSize; /* How many rungs make up the bottom of the Broken Ladder*/
    int skipped; /* How many rungs are missing on the Broken Ladder */

} Ladder;

int isOnLadder(Ladder *ladder, int x, int y);
int canClimb(Ladder *ladder);
int barrelCanDescend(Ladder *ladder);

#endif