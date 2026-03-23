#ifndef BARREL_H
#define BARREL_H

typedef struct { /* Structure for the Barrels */

    int visible; /* No = 0, Yes = 1 */
    int posY, posX; /* Current Position */
    int deltX, deltY; /* Current Horizontal/Veritcal Velocity */ 
    int state; /* Rolling = 0, On Ladder = 1 */ 
    int topL, bottomR; /* Bounds for Hurt Box*/
    int broken; /* No = 0, Yes = 1 */
    int type; /* Normal = 0, Fire = 1 */
    int direction; /* Left = 0, Right = 1 */

} Barrel;

void roll_barrel(Barrel *barrel);
void break_barrel(Barrel *barrel);

#endif