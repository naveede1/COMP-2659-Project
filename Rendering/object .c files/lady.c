#include "lady.h"

int checkVictory(Lady *lady, int playerX, int playerY)
{
    if (!lady->visible)
        return 0;

    if (playerX >= lady->topL &&
        playerX <= lady->bottomR &&
        playerY == lady->posY)
    {
        return 1;
    }

    return 0;
}