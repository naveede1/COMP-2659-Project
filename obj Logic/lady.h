#ifndef LADY_H
#define LADY_H

typedef struct { /* Structure for Pauline */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int state; /* 0 = idle, 1 = win */
   
} Lady;

#endif