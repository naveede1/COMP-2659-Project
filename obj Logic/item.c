#include "item.h"

void spawnItem(Item item) {

    item.visible = 1;

    /* Set Item Worth */
    if (item.type == 0) {         /* Umbrella - 5000 Points */
        item.worth = 5000;
    } else if (item.type == 1) {  /* Purse - 2000 Points */
        item.worth = 2000;
    } else {                      /* Hat - 1000 Points */
        item.worth = 1000;
    }
    
    /* Start the Timer on the Item */
    item.lifetime = 0;
    item.maxLifetime = 20; /* Change if needed */
}
