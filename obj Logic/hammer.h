#ifndef HAMMER_H
#define HAMMER_H

typedef struct { /* Structure for the Hammers */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int state; /* Has the Hammer been grabbed? No = 0, Yes = 1 */

} Hammer;

#endif