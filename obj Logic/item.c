#include "item.h"
#include "mario.h"

#define BETWEEN_ITEMS 400

void spawnItem(Item *item) {

    item->visible = 1;
    item->posX = 278;
    item->posY = 256;

    /* Set Item Worth */
    if (item->type == 0) {         /* Umbrella - 5000 Points */
        item->worth = 5000;
    } else if (item->type == 1) {  /* Purse - 2000 Points */
        item->worth = 2000;
    } else {                      /* Hat - 1000 Points */
        item->worth = 1000;
    }
    
    /* Start the Timer on the Item */
    item->lifetime = 0;
    item->maxLifetime = 20; /* Change if needed */
}

void updateItem (Item *item) {

    item->lifetime;

    if (item->visible == 0) {  /* Handle Spawning Logic */
        if (item->lifetime >= item->maxLifetime) {
            spawnItem(item);
        }

    } else { /* Handle DeSpawning Logic */
        if (item->lifetime >= item->maxLifetime) {
            item->lifetime = 0;
            item->visible = 0;
            item->posX = 0;
        }
    }
}

int checkItem(Mario mario, Item item) { /* Returns 1 if the Barrel Collides with the Hammer, 0 if not*/

    /* Set Marios Collider */
    int jmXright = mario.posX + 15;
    int jmYbottom = mario.posY + 15;

    /* Set Other Objects Collider */
    int itemXright = item.posX + 15;
    int itemYbottom = item.posY + 15;
    
    
    if (mario.posX > item.posX && mario.posX < itemXright || jmXright > item.posX && jmXright < itemXright) {
        if (mario.posY < itemYbottom && mario.posY > item.posY || jmYbottom < itemYbottom && jmYbottom > item.posY) {
            return 1;
        }
    }
    else {
        return 0;   
    }
}