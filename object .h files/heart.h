#ifndef HEART_H
#define HEART_H

typedef struct { /* Structure for the Heart that appears at level end*/

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int broken; /* No = 0, Yes = 1 */

    float animTimer;
    float animRate;

} Heart;

#endif