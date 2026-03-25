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
#include "input.c"

#include "model.h"
#include "raster.c"
#include "clock.c"
#include "item.c"
#include "kong.c"

#include <osbind.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* for random */

#define FRAMERULE 12

Model testModel = {
{1, 236, 352, 0, 0, 1, 1, 0, -1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 306, 322, 300, 316}, /* Jumpman*/

{ {1, 176, 142, 0, 8, 0, 0}, /* Girder 1 */
{1, 272, 106, 0, 3, 0, 0}, 
{1, 304, 142, 2, 5, 0, 0}, 
{1, 192, 202, 1, 13, 0, 0}, 
{1, 176, 234, 2, 13, 0, 0}, 
{1, 192, 290, 1, 13, 0, 0}, 
{1, 176, 322, 2, 13, 0, 0}, 
{1, 272, 368, 1, 8, 0, 0}, 
{1, 176, 368, 0, 6, 0, 0} }, /* Girder 9*/

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

{ {1, 300, 314, 0, 0, 0, 0, 0, 0, 0}, /* Barrel 1 */
{1, 316, 262, 0, 0, 1, 0, 0, 0, 0}, 
{1, 246, 184, 0, 0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0} }, /* Barrel 7 */ 

{0, 240, 352, 0, 0, 1, 0, 0, 0}, /* Spirit */

{0, 358, 300, 0, 0, 2, 0, 0, 0}, /* Item */

{0, 288, 66, 0, 0, 0}, /* Heart */

{1, 352, 78, 5000, 0, 0, 0, 0}, /* Timer */

{1, 240, 11, 1000, 70981}, /* Score */

{1, 186, 48, 3}, /* Lives */ 
};


void render(Model *model, UINT16 *base) {

    renderDK(model->kong,(UINT32 *)base);
    renderMario(model->mario, base);
    renderHeart(model->heart, base);
    renderLady(model->lady,(UINT32 *) base);
    renderSpirit(model->spirit, base);
    
    renderBStack(model->kong, (UINT32 *)base);
    renderOil(model->oil,(UINT32 *) base);
    
    renderHammer(model->hammers[0], base);
    renderHammer(model->hammers[1], base);
    renderItem(model->item, base);

}

void renderLevel(Model *model, UINT32 *base) {

    int i; /* Girder Counter */
    int j; /* Ladder Counter */
    int k; /* Barrel Counter */

    for (i = 0; i < 9; i++)
    {
        renderGirder(model->girders[i], (UINT8 *)base);        
    }

    for (i = 0; i < 15; i++)
    {
        renderLadder(model->ladders[i], (UINT8 *)base);        
    }

    for (i = 0; i < 7; i++)
    {
        renderBarrel(model->barrels[i], (UINT16 *)base);        
    }

    renderBonus(model->timer, base);
    renderLives(model->lives, (UINT8 *)base);
    renderScore(model->score, base);

}

int checkMCollision(int jmXleft, int jmYtop, int otherXleft, int otherYtop, int otherSize) { /* Returns 1 if the Object Collides with Mario, 0 if not*/

    /* Set Marios Collider */
    int jmXright = jmXleft + 15;
    int jmYbottom = jmYtop + 15;

    /* Set Other Objects Collider */
    int otherXright = otherXleft + (otherSize - 1);
    int otherYbottom = otherYtop + (otherSize - 1);
    
    /* Check for possible X position collision */
    if ((jmXleft <= otherXleft <= jmXright) || (jmXleft <= otherXright <= jmXright)) {

        /* Check for possible Y position collision */
        if ((jmYtop <= otherYtop <= jmYbottom) || (jmYtop <= otherYbottom <= jmYbottom)) {

            /* If both conditions are met, there's some form of overlap -> COLLISION! */
            return 1;
        }
    }
    /* If there's no X overlap, it doesnt matter if we check the Y */
    return 0;
}

int main() {
    
    UINT32 *screen = Physbase();
    long nowTime;
    long startTime = getTime();
    long passedTime;

    int gameRunning = 1;

    int timerCounter = 0;
    int timerReset = 0;

    int itemSpawnCheck = 10;
    int itemSpawned = 0;
    int itemStartTimer;

    
    int lastFrameTick = -1; /*Tracks the last frame tick to prevent duplicate updates*/
    int canSpawnBarrel = rand() % 10; /* Random number from 0 to 9 */
    Model *model = &testModel;

    /* Draw static level once */
    clear_screen(screen);
    render(model, screen);
    renderLevel(model, screen);
    renderBonus(model->timer, screen);
    renderLives(model->lives, screen);
    renderScore(model->score, screen);
    renderDK(model->kong, screen);
    renderBStack(model->kong, screen); /*rendering barrel stack besides DK*/

    /* Safety checks */
    if (model->mario.posX < 0){
        model->mario.posX = 0;
    } else if (model->mario.posY < 0) {
        model->mario.posY = 0;
    } else if (model->mario.posX > 624) {
        model->mario.posX = 624;
    } else if (model->mario.posY > 384) {
        model->mario.posY = 384;
    }

    while (gameRunning) {

        nowTime = getTime();
        passedTime = nowTime - startTime;

        if (passedTime % 750 == 0) {

            model->timer.value -= 200;
            clear_region(screen, model->timer.posY + 11, model->timer.posX + 4, 16, 48);
            renderBonus(model->timer, screen);

            if (model->timer.value == 4800) {

                printf("SKILL ISSUE - TIME GAME OVER\n");
                gameRunning = 0;
                /* ADD THE MARIO UPDATE RENDER FUNCTION HERE FOR THE HIT RENDER */
            }
        }
        
        if (passedTime % FRAMERULE == 0 && passedTime != lastFrameTick) { 
        lastFrameTick = passedTime;

        if (passedTime > 5000) {
            printf("GAME OVER\n");
            gameRunning = 0;
        }
        else {
            int oldDKstate = model->kong.state;

            if (oldDKstate != updateKong(&model->kong, canSpawnBarrel)) {
                clear_region(screen, 110, 198, 32, 64); 
                renderDK(model->kong, screen);
            }

            clear_region(screen, model->mario.posY, model->mario.posX, 16, 16);

            model->mario.state = 0;

            if (has_input()) {
                char ch = get_input();

                if (ch == 'a') {
                    model->mario.posX -= 2;
                    model->mario.direction = 0;
                    model->mario.state = 1;
                    model->mario.walkFrame = 1 - model->mario.walkFrame;
                }
                else if (ch == 'd') {
                    model->mario.posX += 2;
                    model->mario.direction = 1;
                    model->mario.state = 1;
                    model->mario.walkFrame = 1 - model->mario.walkFrame;
                }
                else if (ch == 'w') {
                    model->mario.posY -= 2;
                    model->mario.state = 2;
                    model->mario.climbFrame = 1 - model->mario.climbFrame;
                }
                else if (ch == 's') {
                    model->mario.posY += 2;
                    model->mario.state = 2;
                    model->mario.climbFrame = 1 - model->mario.climbFrame;
                }
                else if (ch == 'q') {
                    gameRunning = 0;
                }
            }

            updateMCollision(model->mario);
            renderMario(model->mario, (UINT16 *)screen);
            }
        }
        
    }
    
    return 0;
}