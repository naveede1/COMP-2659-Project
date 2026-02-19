#ifndef HAMMER_H
#define HAMMER_H

typedef struct { /* Structure for the Hammers */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int state; /* Has it been used/picked up? No = 0, Yes = 1 */
    int topL, bottomR; /* Bounds for Pickup Box*/

} Hammer;

#endif