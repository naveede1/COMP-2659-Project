#ifndef OIL_H
#define OIL_H

typedef struct { /* Structure for the Oil Barrel */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int state; /* Barrel ignites when hot by barrel. Not Ignited = 0, Ignited = 1 */
    int requestFireBarrel; /* Signal to DK. No = 0, Yes = 1) */

} Oil;

void updateOil(Oil *oil, float deltaTime);
void igniteOil(Oil *oil);
void notifyFireSpiritDead(Oil *oil);

#endif