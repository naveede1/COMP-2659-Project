#ifndef BARREL_H
#define BARREL_H

#include "girder.h"

typedef struct { /* Structure for the Barrels */

    int visible; /* No = 0, Yes = 1 */
    int posY, posX; /* Current Position */
    int deltX, deltY; /* Current Horizontal/Veritcal Velocity */ 
    int state; /* Rolling = 0, On Ladder = 1 */ 
    int topL, bottomR; /* Bounds for Hurt Box*/
    int broken; /* No = 0, Yes = 1 */
    int type; /* Normal = 0, Fire = 1 */
    int width, height; /* 16x16 */

} Barrel;

void updateBarrel(Barrel *b, float deltaTime);
void rollBarrel(Barrel *b);
void sendDownLadder(Barrel *b);
void breakBarrel(Barrel *b);
boolean is_barrel_grounded(Barrel *barrel, Girder *girders[]);
void apply_gravity_barrel(Barrel *barrel);

#endif