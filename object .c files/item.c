#include "item.h"

void spawnItem(Item *item, int x, int y, int type)
{
    item->visible = 1;
    item->posX = x;
    item->posY = y;
    item->type = type;

    item->lifetime = 0.0f;
    item->maxLifetime = 8.0f;  /* This can be changed and is just a guess for now for testing */
}

void updateItem(Item *item, float deltaTime) /* Counter for how long it's been on-screen */
{
    if (!item->visible) 
        return;

    item->lifetime += deltaTime;

    if (item->lifetime >= item->maxLifetime)
    {
        item->visible = 0;
    }
}

int checkItemPickup(Item *item, int playerX, int playerY) /* Collision Detector, returns the type of the item picked up */
{
    if (!item->visible)
        return -1;

    if (playerX >= item->topL &&
        playerX <= item->bottomR &&
        playerY == item->posY)
    {
        item->visible = 0;
        return item->type;
    }

    return -1;
}
