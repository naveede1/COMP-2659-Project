#include "barrel.h"
#include "mario.h"

long spawnedTime;

void updateBarrels(Barrel barrel[], long nowTime) {
    
    int i;
    for (i = 0; i < 9; i++) {
    
        if(barrel[i].visible == 1) {
            
            spawnedTime = nowTime - barrel[i].timeSpawned;

            if (spawnedTime < 250) {

                barrel[i].posX += 4;
                barrel[i].dropTick = 4;

            } else if (spawnedTime >= 250 && spawnedTime < 760) {

                if (barrel[i].dropTick == 4) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX += 4;
                barrel[i].dropTick++;
                
            } else if (spawnedTime >= 760 && spawnedTime < 930){

                barrel[i].posY += 6;
                barrel[i].dropTick = 2;

            } else  if (spawnedTime >= 930 && spawnedTime < 1520) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX -= 8;
                barrel[i].dropTick++;
            
            } else if (spawnedTime >= 1540 && spawnedTime < 1730){

                barrel[i].posY += 4;
                barrel[i].dropTick = 2;

            } else if (spawnedTime >= 1730 && spawnedTime < 2340) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX += 8;
                barrel[i].dropTick++;

            } else if (spawnedTime >= 2340 && spawnedTime < 2360){

                barrel[i].posX += 4;
            
            } else if (spawnedTime >= 2360 && spawnedTime < 2480){

                barrel[i].posY += 6;
                barrel[i].dropTick = 2;                

            } else if (spawnedTime >= 2480 && spawnedTime < 3090) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX -= 8;
                barrel[i].dropTick++;
        
            } else if (spawnedTime >= 3110 && spawnedTime < 3290){

                barrel[i].posY += 4;
                barrel[i].dropTick = 2;
            
            } else if (spawnedTime >= 3290 && spawnedTime < 3900) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                }     
                barrel[i].posX += 8;
                barrel[i].dropTick++;

            } else if (spawnedTime >= 3900 && spawnedTime < 3920){

                barrel[i].posX += 4;
            
            } else if (spawnedTime >= 3920 && spawnedTime < 4240){

                barrel[i].posY += 2;
                barrel[i].dropTick = 2;        
        
            } else if (spawnedTime >= 4240 && spawnedTime < 4580) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX -= 8;
                barrel[i].dropTick++;
            
            } else if (spawnedTime > 4960) {

                barrel[i].visible = 0;
                barrel[i].timeSpawned = 0;
            
            } else {

                barrel[i].posX -= 4;

            }
        }
    }

    return;
}

int checkBarrels(Mario mario, Barrel barrel[]) { /* Returns the index of a barrel if it was destroyed, -1 otherwise */

    int barNum;
    if (mario.hammerActive == 1) {
        for (barNum = 0; barNum < 9; barNum++) {
            if(barrel[barNum].visible == 1) {
                if(mario.hammerFrame == 0) { /* Hammer Down */
                    if(mario.direction == 0) { /* Mario Left */
                        if(checkHCollision(mario.posX-15, mario.posY+2, barrel[barNum]))
                            return barNum;
                    } else { /* Mario Right */
                        if(checkHCollision(mario.posX+15, mario.posY+2, barrel[barNum]))
                            return barNum;
                    }
                } else { /* Hammer Up */
                    if(mario.direction == 0) { /* Mario Left*/
                        if(checkHCollision(mario.posX+2, mario.posY-15, barrel[barNum]))
                            return barNum;
                    } else { /* Mario Right */
                        if(checkHCollision(mario.posX-2, mario.posY-15, barrel[barNum]))
                            return barNum;
                    }
                }
            }
        }
    }

    return -1;
}

int checkHCollision(int hamXleft, int hamYtop, Barrel barrel) { /* Returns 1 if the Barrel Collides with the Hammer, 0 if not*/

    /* Set Marios Collider */
    int hamXcenter = hamXleft + 7;
    int hamYcenter = hamYtop + 7;

    /* Set Other Objects Collider */
    int barXleft = barrel.posX;
    int barXright = barXleft + 15;
    int barYtop = barrel.posY;
    int barYbottom = barYtop + 15;
    
    if (!barrel.visible) /* Can't die to destroyed barrel */
        return 0;
    
    if (hamXcenter >= barXleft && hamXcenter <= barXright) {
        if (hamYcenter >= barYtop && hamYcenter <= barYbottom) {
            return 1;

        } else {
            return 0;

        }
    } else {
        return 0;
    }
}
