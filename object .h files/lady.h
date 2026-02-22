#ifndef LADY_H
#define LADY_H

typedef struct { /* Structure for Pauline */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int topL, bottomR; /* Bounds for Victory Box*/
   
} Lady;

#endif