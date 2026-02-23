#ifndef LADDER_H
#define LADDER_H

typedef struct { /* Structure for Ladders */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int broken; /* No = 0, Yes = 1 */
    int top, bottom; /* Allows both for the customizing of size and also so barrels/spirits can use this path*/

} Ladder;

#endif