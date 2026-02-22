#include "spirit.h"
#include "girder.h"
#include "ladder.h"

/* Note to future me: Oil Barrel doesn't spawn this, the model actually does after ignition, (don't double call) */
void spawnSpirit(Spirit *s, int x, int y)
{
    s->visible = 1;
    s->posX = x;
    s->posY = y;

    s->direction = 0;   /* starts left (just like the arcade ;) */
    s->deltX = -2;
    s->deltY = 0;
}

void updateSpirit(Spirit *s, Girder girders[], int numGirders, Ladder ladders[], int numLadders)
{
    if (!s->visible)
        return;

    /* Move horizontally */
    s->posX += s->deltX;

    /* Snap to the height of the girder */
    for (int i = 0; i < numGirders; i++)
    {
        if (isOnGirder(&girders[i], s->posX))
        {
            int height = getGirderHeight(&girders[i], s->posX);
            s->posY = height;
        }
    }

    /* Check if the spirit should descend the ladder */
    for (int i = 0; i < numLadders; i++)
    {
        if (isOnLadder(&ladders[i], s->posX, s->posY))
        {
            if (rand() % 5 == 0) /* 20% chance (same as arcade game) */
            {
                s->deltX = 0;
                s->deltY = 2;  /* go down the ladder */
            }
        }
    }

    /* Ladder movement */
    if (s->deltY != 0)
    {
        s->posY += s->deltY;
    }
}