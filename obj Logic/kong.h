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
    float barrelCooldown; /* Time between barrel throws */
    int spawnBarrel; /* 1 when a barrel should spawn */
    int spawnFireBarrel; /* Only 1 when a FIRE barrel should spawn */

} Kong;

/*----- Function: updateKong -----

  PURPOSE: Updates Kong's state machine each game tick.
           Decides whether Kong throws a barrel or mocks
           based on the random roll passed in.

  INPUT: kong (Kong*): pointer to Kong's state
         canSpawnBarrel : random roll 0-9, Kong throws only on 0

  OUTPUT: None

*/

void updateKong(Kong *kong, int canSpawnBarrel);

/*----- Function: requestFireBarrel -----

  PURPOSE: Flags Kong to spawn a fire barrel on his next throw.

  INPUT: kong (Kong*): pointer to Kong's state

  OUTPUT: None

*/

void requestFireBarrel(Kong *kong);

/*----- Function: kongAction -----

  PURPOSE: Decides whether Kong throws a barrel or mocks.
           Guarantees a throw after 1  miss
           to ensure at least one barrel per 140 ticks.(Can change it)

  INPUT: kong (Kong*): pointer to Kong's state
         canSpawnBarrel (int): random roll 0-9, Kong throws only on 0

  OUTPUT: None

*/

static void kongAction(Kong *kong, int canSpawnBarrel);

/*----- Function: kongMock -----

  PURPOSE: Puts Kong into the mocking state, playing his taunt animation.

  INPUT: kong (Kong*): pointer to Kong's state

  OUTPUT: None

*/

static void kongMock(Kong *kong);

/*----- Function: kongSpawner -----

  PURPOSE: Puts Kong into the grab state, beginning the barrel throw sequence.

  INPUT: kong (Kong*): pointer to Kong's state

  OUTPUT: None

*/

static void kongSpawner(Kong *kong);

/*----- Function: finishThrow -----

  PURPOSE: Finishes Kong's barrel throw sequence, spawning a barrel if flagged.

  INPUT: kong (Kong*): pointer to Kong's state

  OUTPUT: None

*/
static void finishThrow(Kong *kong);

#endif
