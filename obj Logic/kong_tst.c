#include <stdio.h>
#include <osbind.h>
#include "clock.h"
#include "raster.h"
#include "kong.h"
#include "rDK.h"



#define KONG_IDLE   0
#define KONG_GRAB   1
#define KONG_HOLD   2
#define KONG_THROW  3
#define KONG_MOCK   4


static void initKong(Kong *kong) {
    kong->visible = 1;
    kong->posX = 198;
    kong->posY = 110;
    kong->state = KONG_IDLE;
    kong->topL = 0;
    kong->bottomR = 0;
    kong->spawnX = 230;
    kong->spawnY = 126;
    kong->stateTimer = 0;
    kong->spawnBarrel = 0;
    kong->spawnFireBarrel = 0;
}

int main() {
    UINT32 *base = (UINT32 *)Physbase();
    Kong kong;
    UINT32 lastTime;
    UINT32 nowTime;
    int running = 1;
    int oldState = -1;
    char input;

    initKong(&kong);
    clear_screen(base);
    renderDK(kong,base);

    lastTime = getTime();

    while (running)
    {
        if (Cconis() != 0)
        {
            input = (char)Cnecin();

            if (input == 'q')
                running = 0;
            else if (input == 'f') {
                requestFireBarrel(&kong);
                printf("Requested FIRE barrel\n");
            }
        }

        nowTime = getTime();

        if (nowTime != lastTime) {
            updateKong(&kong, 1);

            clear_screen(base);
            renderDK(kong,base);

            if (kong.state != oldState) {
                printf("state=%d timer=%lu\n", kong.state, kong.stateTimer);
                oldState = kong.state;
            }

            if (kong.spawnBarrel != 0) {
                printf("Barrel signal = %d\n", kong.spawnBarrel);
                kong.spawnBarrel = 0;
            }

            lastTime = nowTime;
        }
    }

    return 0;
}
