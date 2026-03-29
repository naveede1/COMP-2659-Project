#include "girder.h"

int getGirderHeight(Girder *g, int x)
{
    int width;
    int rise;

    if (!g->visible)
        return -1;

    if (x < g->colLeft || x > g->colRight)
        return -1;

    width = g->colRight - g->colLeft;
    rise = g->size - 1;

    if (g->type == 0 || width == 0)
        return g->posY;

    if (g->type == 1)
        return g->posY - rise + ((x - g->colLeft) * rise) / width;

    return g->posY + ((x - g->colLeft) * rise) / width;
}

int isOnGirder(Girder *g, int x)
{
    if (!g->visible)
        return 0;
    return (x >= g->colLeft && x <= g->colRight) ? 1 : 0;
}