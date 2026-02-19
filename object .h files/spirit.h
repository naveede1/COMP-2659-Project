#ifndef SPIRIT_H
#define SPIRIT_H

typedef struct { /* Structure for the Fire Spirit */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int deltX, deltY; /* Current Horizontal/Veritcal Velocity */ 
    int direction; /* Left = 0, Right = 1 */ 
    int topL, bottomR; /* Bounds for Hurt Box*/

} Spirit;

#endif