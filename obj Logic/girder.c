#include "girder.h"

int getGirderHeight(Girder *g, int x)
{
    int left;
    int right;
    int width;
    int offset;

    if (!g->visible)
        return -1;

    left = g->posX;
    right = g->posX + (g->size * 8) - 1;

    if (x < left || x > right)
        return -1;

    width = right - left + 1;
    offset = x - left;

    if (g->type == 0) {
        return g->posY;
    }
    else if (g->type == 1) {   /* / */
        return g->posY - (offset * 8) / width;
    }
    else {                     /* \ */
        return g->posY + (offset * 8) / width;
    }
}

int isOnGirder(Girder *g, int x)
{
    int left;
    int right;

    if (!g->visible)
        return 0;

    left = g->posX;
    right = g->posX + (g->size * 8) - 1;

    if (x >= left && x <= right)
        return 1;

    return 0;
}