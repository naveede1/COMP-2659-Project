#ifndef KONG_H
#define KONG_H

#include "raster.h"


typedef struct { /* Structure for Donkey Kong */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int state; /* Idle = 0, Grab Barrel = 1, Holding Barrel = 2, Throw Barrel = 3, Mocking = 4 */
    int topL, bottomR; /* Bounds for Hurt Box*/
    int spawnX, spawnY; /* Position the Barrels spawn from */

    UINT32 stateTimer; /* Controls animation timing */
    /*float barrelCooldown; /* Time between barrel throws */
    int spawnBarrel; /* 1 when a barrel should spawn */
    int spawnFireBarrel; /* Only 1 when a FIRE barrel should spawn */

} Kong;

void updateKong(Kong *kong, int canSpawnBarrel);
void requestFireBarrel(Kong *kong);

/*helper functions*/
static void kongAction(Kong *kong, int canSpawnBarrel);
static void kongMock(Kong *kong);
static void kongSpawner(Kong *kong);
static void finishThrow(Kong *kong);
#endif