#include "girder.h"

int getGirderHeight(Girder *g, int x) {
    
    int width, offset;
    int left  = g->posY;  /* horizontal left edge of girder  */
    int right = g->posY + (g->size * 16) - 1; /* horizontal right edge of girder */

    if (!g->visible)
        return -1; /* girder is hidden, ignore it */

    if (x < left || x > right)
        return -1; /* x is outside this girder, ignore it */

    if (g->type == 0)
        return g->posX; /* flat girder — surface height is constant */

    /* Sloped girder — surface height changes as x moves across it.
       We work out how far along the girder x is (offset), then
       calculate how far up or down the slope the surface sits at
       that point, proportional to the total width */
    width  = right - left + 1; /* total horizontal width in pixels */
    offset = x - left; /* how far x is from the left edge */

    if (g->type == 1)           /* / slope — surface rises left to right */
        return g->posX - (offset * g->size) / width;
    else                        /* \ slope — surface falls left to right */
        return g->posX + (offset * g->size) / width;
}

int isOnGirder(Girder *g, int x) {
    int left  = g->posY; /* horizontal left edge  */
    int right = g->posY + (g->size * 16) - 1; /* horizontal right edge */

    if (!g->visible)
        return 0; /* girder is hidden, cannot stand on it */

    return (x >= left && x <= right) ? 1 : 0;
}