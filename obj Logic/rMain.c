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
#include "rBound.c"
#include "splash.c"

 
#include "clock.c"
#include "item.c"
#include "kong.c"
#include "barrel.c"
#include "input.c"
#include "music.c"
#include "psg.c"
#include "girder.c"
#include "mario.c"
#include "ihand.c"
#include "vbl.c"

#include <osbind.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* for random */


#define SCREEN_SIZE 32000
#define FRAMERULE 12

Model testModel = {
/* visible, posX, posY, deltX, deltY, state, direction, climbDir, climbing, collideLadder, onGround, hammerActive,
    hammerTimer, dead, walkFrame, climbFrame, hammerFrame, hammerFrameTimer, hammerHitActive */
{1, 210, 352, 0, 0, 1, 1, 0, -1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 194, 226, 336, 368}, /* Jumpman*/

/* visible, posY, posX, type, size, colLeft, colRight */
/*To Calculate colLeft and colRight 
 using the formula:
 colLeft = posX - (size - 1) / 2
 colRight = posX + (size - 1) / 2
*/
{ {1, 176, 142, 0, 8,  176, 303}, /* Girder 1 */
  {1, 272, 106, 0, 3,  272, 319},
  {1, 304, 142, 2, 5,  304, 383},
  {1, 192, 202, 1, 13, 192, 399},
  {1, 176, 234, 2, 13, 176, 383},
  {1, 192, 290, 1, 13, 192, 399},
  {1, 176, 322, 2, 13, 176, 383},
  {1, 272, 368, 1, 8,  272, 399},
  {1, 176, 368, 0, 6,  176, 319} }, /* Girder 9 */

/* visible, posY, posX, broken, size, topSize, bottomSize, skipped, leftB, rightB, topB, bottomB, update */
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

/* visible, posX, posY, state, topL, bottomR, spawnX, spawnY, stateTimer, spawnBarrel, spawnFireBarrel*/
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, /* Kong */

/* visible, posX, posY, state, requestFireBarrel */
{1, 184, 336, 1, 0}, /* Oil */

/* visible, posX, posY, state */
{ {1, 190, 162, 0}, /* Hammer 1 */
{1, 338, 296, 0} }, /* Hammer 2 */

/* visible, posX, posY, state */
{1, 256, 74, 0}, /* Pauline */ 

/* visible, posX, posY, state, broken, dropTick, timeSpawned */
{ {0, 0, 0, 0, 0, 0}, /* Barrel 1 */
{0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0}, 
{0, 0, 0, 0, 0, 0} }, /* Barrel 9 */ 

/* visible, posX, posY, direction */
{0, 240, 352, 1}, /* Spirit */

/* visible, posX, posY, type, worth, lifetime, maxLifetime */
{0, 358, 300, 2, 0, 0, 0}, /* Item */

/* visible, posX, posY, broken */
{0, 288, 66, 0}, /* Heart */

/* visible, posX, posY, value, startValue */
{1, 352, 78, 5000, 5000}, /* Timer */

/* visible, posX, posY, value, highValue */
{1, 240, 11, 0, 70981}, /* Score */

/* visible, posX, posY, count */
{1, 186, 48, 3}, /* Lives */ 
};

int l = 0;

void render(Model *model, UINT16 *base) {

    renderBounds((UINT8 *)base);
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
    renderScore(model->score, (UINT32 *)base);

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

void draw (Model *model, UINT32 *buffer) {
    
    render(model,(UINT16 *)buffer);
    renderLevel(model, buffer);
    renderDK(model->kong,buffer);
    renderBStack(model->kong,buffer);
    renderLives(model->lives, (UINT8 *)buffer);
    renderScore(model->score, buffer);

}

int splash_screen(UINT16 *base, UINT16 *block) {
    
    int start_game;
    clear_screen((UINT32 *)base);
    render_title(base, block);

    while(!has_input()) {
        char input;
        input = get_input();

        if (input == '\r') {
            return 1;
        } else if (input == 'q') {
            return 0;
        }
    } 
}

void update_game(Model *model, int *gameRunning) {

    int canSpawnBarrel = rand() % 10;
    
    if (vbl_ticks % 140 == 0 && model->timer.value > 0) {
        model->timer.value -= 200;

        if (model->timer.value <= 4000) {
            *gameRunning = 0;
            model->mario.state = 4;
        }
    }

    updateKong(&model->kong, canSpawnBarrel);

    updateMario(&model->mario, model->girders, 9, model->ladders, 15);
    updateMCollision(&model->mario);

    if (model->kong.spawnBarrel == 1)
    {
        model->kong.spawnBarrel = 0;
        model->barrels[l].visible = 1;
        model->barrels[l].posY = 126;
        model->barrels[l].posX = 254;
        model->barrels[l].timeSpawned = vbl_ticks;

        l++;

        if (l > 8)
        {
            l = 0;
        }
    }

    updateBarrels(model->barrels, vbl_ticks);
}

int main() {

    /* --- Allocate buffers --- */
    UINT8 *raw1 = (UINT8 *)Malloc(SCREEN_SIZE + 256);
    UINT8 *raw2 = (UINT8 *)Malloc(SCREEN_SIZE + 256);

    UINT8 *screen1 = (UINT8 *)(((long)raw1 + 255) & 0xFFFFFF00);
    UINT8 *screen2 = (UINT8 *)(((long)raw2 + 255) & 0xFFFFFF00);

    UINT8 *original_screen = Physbase(); /* For resetting buffer at exit */
    UINT8 *front_buffer = Physbase();

    UINT8 *back_buffer  = screen1;
    
    long old_ssp;
    int gameRunning = 1;
    Model *model = &testModel;

    if (splash_screen((UINT16 *)front_buffer, title_block) == 0) {
        Mfree(raw1);
        Mfree(raw2);
        return 0;
    }

    memset(back_buffer, 0, SCREEN_SIZE);

    draw(model, (UINT32 *)back_buffer);

    init_vbl();

    Setscreen(back_buffer, back_buffer, -1);
    
    {
        UINT8 *temp = front_buffer;
        front_buffer = back_buffer;
        back_buffer = temp;
    }
    
    old_ssp = Super(0);
    start_music();
    Super(old_ssp);
        
    while (gameRunning) {

        if (render_request) {
            render_request = 0;

            memset(back_buffer, 0, SCREEN_SIZE);
            inputHandler(model, &gameRunning);

            update_game(model, &gameRunning);

            memset(back_buffer, 0, SCREEN_SIZE);
             /*Note: I know this is repeatation but I am playing around for Double Buffering */

            draw(model, (UINT32 *)back_buffer);

            Setscreen(back_buffer, back_buffer, -1);
            
            {
                UINT8 *temp = front_buffer;
                front_buffer = back_buffer;
                back_buffer = temp;
            }
        }
    }


    old_ssp = Super(0); 
    stop_sound();
    Super(old_ssp);

    shutdown_vbl();
    Setscreen(original_screen, original_screen, -1);

    Mfree(raw1);
    Mfree(raw2);

    return 0;
}