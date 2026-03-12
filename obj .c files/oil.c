#include "oil.h"

/* When a fire barrel hits the Oil Barrel*/
void igniteOil(Oil *oil) {
    
    oil->state = 1;

}

/* When a Fire Spirit dies */
void notifyFireSpiritDead(Oil *oil) {

    oil->fireCheck = 0;
    oil->noFireTimer = 0.0f;  /* start counting */

}

void updateOil(Oil *oil, float deltaTime) {

    // If no fire spirit alive, count time
    if (!oil->fireCheck) {
        oil->noFireTimer += deltaTime;

        if (oil->noFireTimer >= 10.0f) {
            oil->requestFireBarrel = 1;
            oil->noFireTimer = 0.0f; /* reset after signaling */
        }
    }
    else {
        oil->noFireTimer = 0.0f; /* reset if fire exists */
    }
}
