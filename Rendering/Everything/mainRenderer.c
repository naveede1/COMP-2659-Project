#include "rBarrel.c"
#include "rDK.c"
#include "rLady.c"
#include "rMario.c"
#include "rSpirit.c"
#include "rHammer.c"
#include "rItem.c"
#include "rBStack.c"
#include "rGirder.c"
#include "rHeart.c"
#include "rLadder.c"
#include "rOil.c"
#include "rBonus.c"
#include "rLives.c"
#include "rScore.c"

#include "model.h"
#include "raster.c"

#include <osbind.h>
#include <stdio.h>


Model testModel = {
{1, 306, 300, 0, 0, 3, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0}, /* Jumpman*/

{ {1, 176, 142, 0, 8, 0, 0}, /* Girder 1 */
{1, 272, 106, 0, 3, 0, 0}, 
{1, 304, 142, 2, 5, 0, 0}, 
{1, 192, 202, 1, 13, 0, 0}, 
{1, 176, 234, 2, 13, 0, 0}, 
{1, 192, 290, 1, 13, 0, 0}, 
{1, 176, 322, 2, 13, 0, 0}, 
{1, 272, 368, 1, 8, 0, 0}, 
{1, 176, 368, 0, 6, 0, 0} }, /* Girder 9*/

{{1, 248, 78, 0, 0, 0, 0, 0, 8, 0, 0, 0}, /* Ladder 1 */
{1, 264, 78, 0, 0, 0, 0, 0, 8, 0, 0, 0},
{1, 312, 112, 0, 0, 0, 0, 0, 4, 0, 0, 0}, 
{1, 272, 150, 1, 0, 0, 0, 0, 6, 1, 3, 2}, 
{1, 360, 153, 0, 0, 0, 0, 0, 5, 0, 0, 0},
{1, 208, 207, 0, 0, 0, 0, 0, 4, 0, 0, 0},
{1, 248, 206, 0, 0, 0, 0, 0, 4, 0, 0, 0},
{1, 344, 199, 1, 0, 0, 0, 0, 6, 1, 2, 3},
{1, 256, 247, 1, 0, 0, 0, 0, 5, 1, 2, 2},
{1, 320, 251, 0, 0, 0, 0, 0, 4, 0, 0, 0},
{1, 360, 252, 0, 0, 0, 0, 0, 4, 0, 0, 0},
{1, 208, 295, 0, 0, 0, 0, 0, 4, 0, 0, 0},
{1, 288, 291, 0, 0, 0, 0, 0, 5, 0, 0, 0},
{1, 272, 336, 1, 0, 0, 0, 0, 4, 1, 1, 2},
{1, 356, 340, 0, 0, 0, 0, 0, 3, 0, 0, 0} }, /* Ladder 15 */ 

{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, /* Kong */

{1, 184, 336, 0, 0, 0, 0, 1, 0}, /* Oil */

{ {1, 190, 162, 0, 0, 0}, /* Hammer 1 */
{1, 338, 296, 0, 0, 0} }, /* Hammer 2 */

{1, 256, 74, 0, 0, 0}, /* Pauline */ 

{ {1, 300, 314, 0, 0, 0, 0, 0, 0, 0}, /* Barrel 1 */
{1, 316, 262, 0, 0, 1, 0, 0, 0, 0}, 
{1, 246, 184, 0, 0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0} }, /* Barrel 7 */ 

{1, 240, 352, 0, 0, 1, 0, 0, 0}, /* Spirit */

{ {0, 0, 200, 0, 0, 0, 0, 0}, /* Item 1 */
{0, 0, 200, 0, 0, 1, 0, 0},  
{0, 0, 200, 0, 0, 2, 0, 0} },  /* Item 3 */

{0, 288, 66, 0, 0, 0}, /* Heart */

{1, 352, 78, 0, 0, 0, 0, 0}, /* Timer */

{1, 240, 11, 0, 981}, /* Score */

{1, 186, 48, 3}, /* Lives */ 
};

void render(Model *model, UINT32 *base) {

    int i; /* Girder Counter */
    int j; /* Ladder Counter */
    int k; /* Barrel Counter */

    clear_screen(base);

    renderDK(model->kong, base);
    renderMario(model->mario, base);
    renderHeart(model->heart, base);
    renderLady(model->lady, base);
    renderSpirit(model->spirit, base);
    
    renderBStack(model->kong, base);
    renderOil(model->oil, base);
    
    renderBonus(model->timer, base);
    renderLives(model->lives, base);
    renderScore(model->score, base);

    renderHammer(model->hammers[0], base);
    renderHammer(model->hammers[1], base);
    renderItem(model->items[0], base);
    renderItem(model->items[1], base);
    renderItem(model->items[2], base);

    for (i = 0; i < 9; i++)
    {
        renderGirder(model->girders[i], base);        
    }

    for (i = 0; i < 15; i++)
    {
        renderLadder(model->ladders[i], base);        
    }

    for (i = 0; i < 7; i++)
    {
        renderBarrel(model->barrels[i], base);        
    }

}

int main() {

    UINT32 *base = Physbase(); 
    
    Model *model; 
    model = &testModel;

    render(model, base);

    return 0;
}

