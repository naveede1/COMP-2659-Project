#ifndef TIMER_H
#define TIMER_H

typedef struct { /* Structure for the Timer */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
   
    /* This took a bit to figure out and some help from Chat to fill in the gaps, lmk if you need an explanation */
    int value;        /* current bonus score (e.g. 5000) */
    int startValue;   /* starting bonus */
    float tickTimer;  /* internal countdown timer */
    float tickRate;   /* how often it decreases (seconds) */
    int active;       /* is timer running? */

} Timer;

#endif