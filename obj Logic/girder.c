#include "girder.h"

int getGirderHeight(Girder *g, int x)
{
    int width, offset;
    int left  = g->posY;
    int right = g->posY + (g->size * 16) - 1;  /* was size*8 */

    if (!g->visible)   return -1;
    if (x < left || x > right) return -1;

    if (g->type == 0)
        return g->posX;

    width  = right - left + 1;
    offset = x - left;

    if (g->type == 1)
        return g->posX - (offset * g->size) / width;
    else
        return g->posX + (offset * g->size) / width;
}

int isOnGirder(Girder *g, int x)
{
    int left  = g->posY;
    int right = g->posY + (g->size * 16) - 1;  /* was size*8 */

    if (!g->visible) return 0;
    return (x >= left && x <= right) ? 1 : 0;
}