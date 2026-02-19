#ifndef LIVES_H
#define LIVES_H

typedef struct { /* Structure for the Lives counter */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int value; /* How many lives the player has */
   

} Lives;

#endif