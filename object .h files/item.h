#ifndef ITEM_H
#define ITEM_H

typedef struct { /* Structure for Pauline's Items */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int topL, bottomR; /* Bounds for Pickup Box*/
    int type; /* Umbrella = 0, Purse = 1, Hat = 2 */
    float lifetime; /* How long the item has been visible for */
    float maxLifetime; /* The longest it can be visible before disappearing */

} Item;

#endif