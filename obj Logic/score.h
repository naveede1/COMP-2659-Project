#ifndef SCORE_H
#define SCORE_H

typedef struct { /* Structure for the Score Counter */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    long value; /* Current Score */
    long highScore; /* High Score */

} Score;

#endif