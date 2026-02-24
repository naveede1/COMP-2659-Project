#ifndef KONG_H
#define KONG_H

typedef struct { /* Structure for Donkey Kong */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int state; /* Idle = 0, Grab Barrel = 1, Throw Barrel = 2 */
    int topL, bottomR; /* Bounds for Hurt Box*/
    int spawnX, spawnY; /* Position the Barrels spawn from */

    float stateTimer; /* Controls animation timing */
    float barrelCooldown; /* Time between barrel throws */
    int spawnBarrel; /* 1 when a barrel should spawn */
    int spawnFireBarrel; /* Only 1 when a FIRE barrel should spawn */

} Kong;

void updateKong(Kong *kong, float deltaTime);
void requestFireBarrel(Kong *kong);

#endif