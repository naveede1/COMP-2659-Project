#include "item.h"
#include <stdio.h>

void spawnItem(Item item, int x, int y) {

    item.visible = 1;
    item.posX = x;
    item.posY = y;

    /* Generate a random number using the rand() function */
    int value = rand();

    /* Randomize Item Type */
    if (value % 10 == 0) {              /* Umbrella - 5000 Points, 10% */
        item.type == 0
        item.worth == 5000;
    } else if (0 < (value % 10) <= 3) { /* Purse - 2000 Points, 30% */
        item.type == 1
        item.worth == 2000;
    } else {                            /* Hat - 1000 Points, 60% */
        item.type == 1
        item.worth == 1000;
    }
    
    /* Start the Timer on the Item */
    item.lifetime = 0;
    item.maxLifetime = 20; /* Change if needed */
}
