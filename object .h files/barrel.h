#ifndef BARREL_H
#define BARREL_H

typedef struct { /* Structure for the Barrels */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int deltX, deltY; /* Current Horizontal/Veritcal Velocity */ 
    int state; /* Rolling = 0, On Ladder = 1 */ 
    int topL, bottomR; /* Bounds for Hurt Box*/
    int broken; /* No = 0, Yes = 1 */
    int type; /* Normal = 0, Fire = 1 */

} Barrel;

void updateBarrel(Barrel *b, float deltaTime);
void rollBarrel(Barrel *b);
void sendDownLadder(Barrel *b);
void breakBarrel(Barrel *b);

#endif