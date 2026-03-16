#include "clock.h"

UINT32 getTime() {

    long currTime;

    long *timer = (long *)0x0462; /* Location of 70Hz Timer (+70/s)*/
    long old_ssp;

    old_ssp = Super(0); /* Entering Privileged Mode */

    currTime = *timer;

    Super(old_ssp); /* Exiting Privileged Mode */

    return currTime;
}