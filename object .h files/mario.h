#ifndef MARIO_H
#define MARIO_H

typedef struct { /* Structure for Jumpman */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int deltX, deltY; /* Current Horizontal/Veritcal Velocity */ 
    int state; /* Standing = 0, Walking = 1, Climbing = 2, Jumping = 3, Dead (Falling off screen) = 4 */ 
    int hammering; /* No = 0, Yes = 1 */
    int dead; /* Should I be falling offscreen? No = 0, Yes = 1 */

} Mario;

#endif