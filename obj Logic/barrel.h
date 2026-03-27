#ifndef BARREL_H
#define BARREL_H

typedef struct { /* Structure for the Barrels */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int deltX, deltY; /* Current Horizontal/Veritcal Velocity */ 
    int state; /* Rolling = 0, On Ladder = 1 */ 
    int topL, bottomR; /* Bounds for Hurt Box*/
    int broken; /* No = 0, Yes = 1 */
    int dropTick; /* Normal = 0, Fire = 1 */
    long timeSpawned; /* The time when the barrel was first spawned */

} Barrel;

void updateBarrels(Barrel barrel[], long nowTime);

#endif