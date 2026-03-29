#ifndef SPIRIT_H
#define SPIRIT_H

typedef struct { /* Structure for the Fire Spirit */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int direction; /* Left = 0, Right = 1 */ 

} Spirit;

#endif