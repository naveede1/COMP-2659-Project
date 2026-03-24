#ifndef ITEM_H
#define ITEM_H

typedef struct { /* Structure for Pauline's Items */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int oppX, oppY; /* Bounds for Pickup Box*/
    int type; /* Umbrella = 0, Purse = 1, Hat = 2 */
    int worth; /* How much the item spawned is worth */
    int lifetime; /* How many tickthe item has been visible for */
    int maxLifetime; /* How many ticks it can be visible before disappearing */

} Item;

void spawnItem(Item item);

#endif