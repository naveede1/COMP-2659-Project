#include "kong.h"
#include "clock.h"

/*Kong states*/
#define KONG_IDLE   0
#define KONG_GRAB   1
#define KONG_HOLD   2
#define KONG_THROW  3
#define KONG_MOCK   4

/* timing in 70 Hz ticks*/
#define IDLE_TICKS   70
#define GRAB_TICKS   18
#define HOLD_TICKS   18
#define THROW_TICKS  18
#define MOCK_TICKS   20

/* barrel spawn signals */
#define NO_BARREL      0
#define NORMAL_BARREL  1
#define FIRE_BARREL    2

void updateKong(Kong *kong, int canSpawnBarrel) {
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
            if (kong->stateTimer >= MOCK_TICKS) {
                kong->state = KONG_IDLE;
                kong->stateTimer = 0;
            }
            break;

        default:
            kong->state = KONG_IDLE;
            kong->stateTimer = 0;
            break;
    }
}

static void kongAction(Kong *kong, int canSpawnBarrel) {
    UINT32 currTime = getTime();
    kong->stateTimer = 0;
    if (!canSpawnBarrel) {
        kongMock(kong);
        return;
    }
    if ((currTime & 1) == 0)
        kongMock(kong);
    else
        kongSpawner(kong);
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
    if (kong->spawnFireBarrel) {
        kong->spawnBarrel = FIRE_BARREL;
        kong->spawnFireBarrel = 0;
    }
    else
        kong->spawnBarrel = NORMAL_BARREL;
    kong->state = KONG_IDLE;
    kong->stateTimer = 0;
}

void requestFireBarrel(Kong *kong) {
    kong->spawnFireBarrel = 1;
}