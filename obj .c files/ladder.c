#include "ladder.h"

int isOnLadder(Ladder *ladder, int x, int y) {

    if (!ladder->visible)
        return 0;

    if (x >= ladder->left &&
        x <= ladder->right &&
        y >= ladder->top &&
        y <= ladder->bottom)
        return 1;

    return 0;

}

int canClimb(Ladder *ladder) {

    if (ladder->broken)
        return 0;

    return 1;

}

int barrelCanDescend(Ladder *ladder) {
    
    return ladder->visible;

}