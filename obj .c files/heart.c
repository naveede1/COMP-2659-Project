#include "heart.h"

void showHeart(Heart *heart, int x, int y)
{
    heart->visible = 1;
    heart->posX = x;
    heart->posY = y;
    heart->broken = 0;
    heart->animTimer = 0;
}

void updateHeart(Heart *heart, float deltaTime)
{
    if (!heart->visible)
        return;

    heart->animTimer += deltaTime;

    if (heart->animTimer >= 1.0f && !heart->broken)
    {
        heart->broken = 1;   /* play break animation */
    }
}