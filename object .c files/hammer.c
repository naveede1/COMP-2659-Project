#include "hammer.h"

int checkHammerPickup(Hammer *h, int playerX, int playerY)
{
    if (!h->visible || h->state == 1)
        return 0;

    if (playerX >= h->topL &&
        playerX <= h->bottomR &&
        playerY == h->posY)
    {
        h->state = 1;
        h->visible = 0;
        return 1; /* signal pickup */
    }

    return 0;
}

void deactivateHammer(Hammer *h)
{
    h->state = 0;
    h->visible = 1;
}
