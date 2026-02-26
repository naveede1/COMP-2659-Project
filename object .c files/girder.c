#include "girder.h"

int getGirderHeight(Girder *g, int x)
{
    if (!g->visible)
        return -1;

    if (x < g->left || x > g->right)
        return -1;

    float slope = (float)(g->topRight - g->topLeft) / (g->right - g->left);

    int y = g->topLeft + slope * (x - g->left);

    return y;
}

int isOnGirder(Girder *g, int x)
{
    if (!g->visible)
        return 0;

    if (x >= g->left && x <= g->right)
        return 1;

    return 0;
}