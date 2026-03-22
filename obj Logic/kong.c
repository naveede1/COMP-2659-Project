#include "kong.h"
#include "clock.h"

/*Kong states*/
#define KONG_IDLE   0
#define KONG_GRAB   1
#define KONG_HOLD   2
#define KONG_THROW  3
#define KONG_MOCK   4

 /*Duration of each state in 70Hz clock ticks.
    These are set low for faster testing - increase for final game */
#define IDLE_TICKS   18
#define GRAB_TICKS   18
#define HOLD_TICKS   18
#define THROW_TICKS  18
#define MOCK_TICKS   18

/* barrel spawn signals */
#define NO_BARREL      0
#define NORMAL_BARREL  1


int updateKong(Kong *kong, int canSpawnBarrel) {
    kong->stateTimer++;
    switch (kong->state) {
        case KONG_IDLE:
            if (kong->stateTimer >= IDLE_TICKS) 
                kongAction(kong, canSpawnBarrel);
            break;

        case KONG_GRAB:
            if (kong->stateTimer >= GRAB_TICKS) {
                kong->state = KONG_HOLD;
                kong->stateTimer = 0;
            }
            break;

        case KONG_HOLD:
            if (kong->stateTimer >= HOLD_TICKS){
                kong->state = KONG_THROW;
                kong->stateTimer = 0;
            }
            break;

        case KONG_THROW:
            if (kong->stateTimer >= THROW_TICKS)
                finishThrow(kong);
            break;

        case KONG_MOCK:
            /* Return to idle after mocking */
            if (kong->stateTimer >= MOCK_TICKS) {
                kong->state = KONG_IDLE;
                kong->stateTimer = 0;
            }
            break;

        default:
         /* reset to idle (for safety) */
            kong->state = KONG_IDLE;
            kong->stateTimer = 0;
            break;
    }

    return kong->state;
}

static void kongAction(Kong *kong, int canSpawnBarrel) {
    static int missedThrows = 0;
    kong->stateTimer = 0;

    if (missedThrows >= 1) {
        /* Guarantee a throw after 1 consecutive mocks */
        missedThrows = 0;
        kongSpawner(kong);
        return;
    }
    if (canSpawnBarrel == 0) {
        /* Random roll hit 0 - throw a barrel */
        missedThrows = 0;
        kongSpawner(kong);
    } else {
        /* Random roll missed - mock */
        missedThrows++;
        kongMock(kong);
    }
}

static void kongMock(Kong *kong) {
    kong->state = KONG_MOCK;
    kong->stateTimer = 0;
}

static void kongSpawner(Kong *kong) {
    kong->state = KONG_GRAB;
    kong->stateTimer = 0;
}

static void finishThrow(Kong *kong) {
    kong->spawnBarrel = NORMAL_BARREL;
    kong->state = KONG_IDLE;
    kong->stateTimer = 0;
}
