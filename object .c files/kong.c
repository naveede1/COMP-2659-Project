#include "kong.h"

#define IDLE_TIME 2.0f
#define GRAB_TIME 0.5f
#define THROW_TIME 0.5f

void updateKong(Kong *kong, float deltaTime)
{
    kong->stateTimer += deltaTime;

    switch (kong->state) /* Switch looks at cases and uses the state to perform that action */
    {
        case 0: /* IDLE */

            if (kong->stateTimer >= IDLE_TIME)
            {
                kong->state = 1; /* Grab */
                kong->stateTimer = 0;
            }

            break;

        case 1: /* GRAB */

            if (kong->stateTimer >= GRAB_TIME)
            {
                kong->state = 2; /* Throw */
                kong->stateTimer = 0;
            }

            break;

        case 2: /* THROW */

            if (kong->stateTimer >= THROW_TIME)
            {
                /* Spawn barrel */
                if (kong->spawnFireBarrel)
                {
                    kong->spawnBarrel = 2;  /* 2 = Fire Barrel */
                    kong->spawnFireBarrel = 0;
                }
                else
                {
                    kong->spawnBarrel = 1;  /* 1 = Normal Barrel */
                }

                kong->state = 0; /* Back to idle */
                kong->stateTimer = 0;
            }

            break;

        /* To future me, don't need a Default/Fallback Case as only case 0-2 can be selected */

    }
}

void requestFireBarrel(Kong *kong) {

    kong->spawnFireBarrel = 1;

}