#ifndef TIMER_H
#define TIMER_H

typedef struct { /* Structure for the Timer */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int value;        /* current bonus score (e.g. 5000) */
    int startValue;   /* starting bonus */

} Timer;

#endif