#include <stdio.h>
#include <osbind.h>
#include <unistd.h>
#include "raster.c" /* Changing this from .h to .c */

#include "model.h"
#include "girder.h" 
#include "mario.c"
#include "rMario.c"
#include "rGirder.c" /* Changing this from .h to .c */

/* 

JUMPMAN TEST VALUES 

{1, 306, 300, 0, 0, 3, 0, 0, -1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 306, 322, 300, 316, 16, 16} (from rMain.c)
{1, 180, 130, 0, 0, 3, 0, 0, -1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 306, 322, 300, 316, 16, 16} (grounded)
{1, 200, 306, 0, 0, 3, 0, 0, -1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 306, 322, 300, 316, 16, 16} (grounded)

*/

Model testModel = {
{1, 306, 300, 0, 0, 3, 0, 0, -1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 306, 322, 300, 316, 16, 16}, /* Jumpman*/

{ {1, 176, 142, 0, 8, 0, 0, 8, 8}, /* Girder 1 */
{1, 272, 106, 0, 3, 0, 0, 8, 8}, 
{1, 304, 142, 2, 5, 0, 0, 8, 8}, 
{1, 192, 202, 1, 13, 0, 0, 8, 8}, 
{1, 176, 234, 2, 13, 0, 0, 8, 8}, 
{1, 192, 290, 1, 13, 0, 0, 8, 8}, 
{1, 176, 322, 2, 13, 0, 0, 8, 8}, 
{1, 272, 368, 1, 8, 0, 0, 8, 8}, 
{1, 176, 368, 0, 6, 0, 0, 8, 8} }, /* Girder 9*/

{{1, 248, 78, 0, 8, 0, 0, 0, 0, 0, 0, 0, 1}, /* Ladder 1 */
{1, 264, 78, 0, 8, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 312, 112, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1}, 
{1, 272, 150, 1, 6, 1, 3, 2, 0, 0, 0, 0, 1}, 
{1, 360, 153, 0, 5, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 208, 207, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 248, 206, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 344, 199, 1, 6, 1, 2, 3, 0, 0, 0, 0, 1},
{1, 256, 247, 1, 5, 1, 2, 2, 0, 0, 0, 0, 1},
{1, 320, 251, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 360, 252, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 208, 295, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 288, 291, 0, 5, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 272, 336, 1, 4, 1, 1, 2, 0, 0, 0, 0, 1},
{1, 356, 340, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1} }, /* Ladder 15 */ 

/*visible, posX, posY, state, topL, bottomR, spawnX, spawnY, stateTimer, spawnBarrel, spawnFireBarrel*/
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, /* Kong */

{1, 184, 336, 0, 0, 0, 0, 1, 0}, /* Oil */

{ {1, 190, 162, 0, 0, 0}, /* Hammer 1 */
{1, 338, 296, 0, 0, 0} }, /* Hammer 2 */

{1, 256, 74, 0, 0, 0}, /* Pauline */ 

{ {1, 300, 314, 0, 0, 0, 0, 0, 0, 0, 16, 16}, /* Barrel 1 */
{1, 316, 262, 0, 0, 1, 0, 0, 0, 0, 16, 16}, 
{1, 246, 184, 0, 0, 0, 0, 0, 0, 0, 16, 16}, 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16}, 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16}, 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16}, 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16} }, /* Barrel 7 */ 

{1, 240, 352, 0, 0, 1, 0, 0, 0}, /* Spirit */

{ {0, 0, 200, 0, 0, 0, 0, 0}, /* Item 1 */
{0, 0, 200, 0, 0, 1, 0, 0},  
{0, 0, 200, 0, 0, 2, 0, 0} },  /* Item 3 */

{0, 288, 66, 0, 0, 0}, /* Heart */

{1, 352, 78, 0, 0, 0, 0, 0}, /* Timer */

{1, 240, 11, 0, 981}, /* Score */

{1, 186, 48, 3}, /* Lives */ 
};

void grounded(Model *model, UINT32 *base) {

    int i;
    boolean r_false;

    clear_screen(base);

    /* Render the level */
    for (i = 0; i < 9; i++) {
        renderGirder(model->girders[i], (UINT8 *)base);        
    }

    renderMario(model->mario, (UINT16 *)base);

    if (is_mario_grounded(&model->mario, model->girders) == FALSE) {
        printf("Jumpman is not grounded.\n");
    } else {
        printf("Jumpman is grounded.\n");
    }

    /* Re-render the screen */

    sleep(2);

    clear_screen(base);

    for (i = 0; i < 9; i++) {
        renderGirder(model->girders[i], (UINT8 *)base);        
    }

    renderMario(model->mario, (UINT16 *)base);
}

void test_gravity(Model *model, UINT32 *base) {

    int i;

    while (!is_mario_grounded(&model->mario, model->girders)) {

        apply_gravity_mario(&model->mario, model->girders);

        clear_screen(base);

        for (i = 0; i < 9; i++) {
            renderGirder(model->girders[i], (UINT8 *)base);        
        }

        renderMario(model->mario, (UINT16 *)base);

        sleep(1);

    }

    printf("Jumpman is grounded.\n");

}

int main() {

    UINT32 *base = Physbase();

    /* Girder test_girder_1 = {1, 192, 202, 0, 3, 0, 0}; */

    /* Mario test_mario_1 = {1, 218, 160, 0, 0, 3, 0, 0, -1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 306, 322, 300, 316}; */

    /* grounded(&testModel, base); */
    test_gravity(&testModel, base);
    
    return 0;
}