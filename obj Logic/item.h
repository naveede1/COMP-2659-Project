#ifndef ITEM_H
#define ITEM_H

typedef struct { /* Structure for Pauline's Items */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int type; /* Umbrella = 0, Purse = 1, Hat = 2 */
    int worth; /* How much the item spawned is worth */
    long lifetime; /* How long the item has been in it's current state for */
    long maxLifetime; /* How long CAN the item be visible for */

} Item;

#endif