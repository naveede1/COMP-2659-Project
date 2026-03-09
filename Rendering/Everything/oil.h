#ifndef OIL_H
#define OIL_H

typedef struct { /* Structure for the Oil Barrel */

    int visible; /* No = 0, Yes = 1 */
    int posX, posY; /* Current Position */
    int topL, bottomR; /* Bounds for Hurt Box*/
    int fireCheck; /* Checks if a fire spirit is alive. If no for 10s, signal Fire Barrel. No = 0, Yes = 1 */
    int noFireTimer; /* counts seconds without fire */
    int state; /* Barrel ignites when hot by barrel. Not Ignited = 0, Ignited = 1 */
    int requestFireBarrel; /* Signal to DK. No = 0, Yes = 1) */

} Oil;

void updateOil(Oil *oil, float deltaTime);
void igniteOil(Oil *oil);
void notifyFireSpiritDead(Oil *oil);

#endif