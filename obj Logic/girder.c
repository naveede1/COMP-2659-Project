#include "girder.h"

int getGirderHeight(Girder *g, int x)
{
    int left;
    int right;
    int width;
    int offset;

    if (!g->visible)
        return -1;

    left  = g->posY;                      /* posY = screen X = horizontal left edge */
    right = g->posY + (g->size * 8) - 1;

    if (x < left || x > right)
        return -1;

    width  = right - left + 1;
    offset = x - left;

    if (g->type == 0) {
        return g->posX;                   /* posX = screen Y = height */
    }
    else if (g->type == 1) {             /* / slope */
        return g->posX - (offset * 8) / width;
    }
    else {                               /* \ slope */
        return g->posX + (offset * 8) / width;
    }
}

int isOnGirder(Girder *g, int x)
{
    int left;
    int right;

    if (!g->visible)
        return 0;

    left  = g->posY;                      /* posY = screen X */
    right = g->posY + (g->size * 8) - 1;

    return (x >= left && x <= right) ? 1 : 0;
}