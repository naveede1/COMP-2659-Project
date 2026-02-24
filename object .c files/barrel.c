#include "barrel.h"
#include "oil.h"
#include "ladder.h"

#define GRAVITY 1
#define ROLL_SPEED 2
#define LADDER_SPEED 2

void updateBarrel(Barrel *b, Oil *oil, Ladder *ladder, float deltaTime)
{
    if (!b->visible || b->broken)
        return;

    switch (b->state)
    {
        case 0: /* ROLLING */
            rollBarrel(b);
            break;

        case 1: /* ON LADDER */
            b->posY += LADDER_SPEED;
            break;
    }
    /*When spawning use: "barrel.type = 1;"*/
    if (b->type == 1 && (b->posX == oil->bottomR)) /*(IN COLLISION LOGIC)*/
    {
        igniteOil(&oil);
        breakBarrel(&b);
    }

    if (isOnLadder(ladder, b->posX, b->posY))
    {
        if (rand() % 4 == 0)
            sendDownLadder(b);
    }
}

void rollBarrel(Barrel *b)
{
    b->posX += b->deltX;

    /* Gravity pulling downward */
    b->posY += GRAVITY;
}

void sendDownLadder(Barrel *b)
{
    b->state = 1; /* On ladder */
    b->deltX = 0;
    b->deltY = LADDER_SPEED;
}
/* When barrel reaches next platform: Use "b->state = 0"; (back to rolling) */

void breakBarrel(Barrel *b)
{
    b->broken = 1;
    b->visible = 0;
}