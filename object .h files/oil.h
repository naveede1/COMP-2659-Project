#ifndef OIL_H
#define OIL_H

typedef struct { /* Structure for the Oil Barrel */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int topL, bottomR; /* Bounds for Hurt Box*/
    int fire_check; /* Checks if a fire spirit is alive. If no for 10s, signal Fire Barrel. No = 0, Yes = 1 */

} Oil;

#endif