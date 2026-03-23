#include "barrel.h"
#include "oil.h"
#include "ladder.h"

#define GRAVITY 1
#define ROLL_SPEED 2
#define LADDER_SPEED 2

void roll_barrel(Barrel *barrel) {
    if (barrel->direction == 0) {
        barrel->posY--;
    } else {
        barrel->posY++;
    }
}
