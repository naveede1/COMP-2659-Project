#include "barrel.h"
#include "mario.h"

long spawnedTime;

void updateBarrels(Barrel barrel[], long nowTime) {
    
    int i;
    for (i = 0; i < 9; i++) {
    
        if(barrel[i].visible == 1) {
            
            spawnedTime = nowTime - barrel[i].timeSpawned;

            if (spawnedTime < 350) {

                barrel[i].posX += 4;
                barrel[i].dropTick = 4;

            } else if (spawnedTime >= 350 && spawnedTime < 1120) {

                if (barrel[i].dropTick == 4) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX += 4;
                barrel[i].dropTick++;
                
            } else if (spawnedTime >= 1120 && spawnedTime < 1400){

                barrel[i].posY += 6;
                barrel[i].dropTick = 2;

            } else  if (spawnedTime >= 1400 && spawnedTime < 2340) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX -= 8;
                barrel[i].dropTick++;
            
            } else if (spawnedTime >= 2340 && spawnedTime < 2620){

                barrel[i].posY += 4;
                barrel[i].dropTick = 1;

            } else if (spawnedTime >= 2620 && spawnedTime < 3540) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX += 8;
                barrel[i].dropTick++;

            } else if (spawnedTime >= 3540 && spawnedTime < 3740){

                barrel[i].posY += 6;
                barrel[i].dropTick = 2;                

            } else if (spawnedTime >= 3740 && spawnedTime < 4640) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX -= 8;
                barrel[i].dropTick++;
            
            } else if (spawnedTime >= 4640 && spawnedTime < 4680){

                barrel[i].posX -= 4;
            
            } else if (spawnedTime >= 4680 && spawnedTime < 4950){

                barrel[i].posY += 4;
                barrel[i].dropTick = 2;
            
            } else if (spawnedTime >= 4950 && spawnedTime < 5820) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                }     
                barrel[i].posX += 8;
                barrel[i].dropTick++;
            
            } else if (spawnedTime >= 5820 && spawnedTime < 5880){

                barrel[i].posX += 8;
            
            } else if (spawnedTime >= 5880 && spawnedTime < 6340){

                barrel[i].posY += 2;
                barrel[i].dropTick = 2;        
        
            } else if (spawnedTime >= 6340 && spawnedTime < 6840) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX -= 8;
                barrel[i].dropTick++;
            
            } else if (spawnedTime > 7560) {

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
