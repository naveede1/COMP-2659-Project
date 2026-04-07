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

            } else  if (spawnedTime >= 930 && spawnedTime < 2160) {

                if (barrel[i].dropTick == 4) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX -= 4;
                barrel[i].dropTick++;
            
            } else if (spawnedTime >= 2160 && spawnedTime < 2350){

                barrel[i].posY += 4;
                barrel[i].dropTick = 2;

            } else if (spawnedTime >= 2350 && spawnedTime < 3560) {

                if (barrel[i].dropTick == 4) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX += 4;
                barrel[i].dropTick++;
            
            } else if (spawnedTime >= 3560 && spawnedTime < 3680){

                barrel[i].posY += 6;
                barrel[i].dropTick = 2;                

            } else if (spawnedTime >= 3680 && spawnedTime < 4900) {

                if (barrel[i].dropTick == 4) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX -= 4;
                barrel[i].dropTick++;
        
            } else if (spawnedTime >= 4900 && spawnedTime < 5090){

                barrel[i].posY += 4;
                barrel[i].dropTick = 2;
            
            } else if (spawnedTime >= 5090 && spawnedTime < 6320) {

                if (barrel[i].dropTick == 4) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                }     
                barrel[i].posX += 4;
                barrel[i].dropTick++;

            } else if (spawnedTime >= 6320 && spawnedTime < 6640){

                barrel[i].posY += 2;
                barrel[i].dropTick = 2;        
        
            } else if (spawnedTime >= 6640 && spawnedTime < 7180) {

                if (barrel[i].dropTick == 4) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX -= 4;
                barrel[i].dropTick++;
            
            } else if (spawnedTime > 7700) {

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
                        if(checkHCollision(mario.posX-15, mario.posY+2, barrel[barNum].posX, barrel[barNum].posY))
                            return barNum;
                    } else { /* Mario Right */
                        if(checkHCollision(mario.posX+15, mario.posY+2, barrel[barNum].posX, barrel[barNum].posY))
                            return barNum;
                    }
                } else { /* Hammer Up */
                    if(mario.direction == 0) { /* Mario Left*/
                        if(checkHCollision(mario.posX+2, mario.posY-15, barrel[barNum].posX, barrel[barNum].posY))
                            return barNum;
                    } else { /* Mario Right */
                        if(checkHCollision(mario.posX-2, mario.posY-15, barrel[barNum].posX, barrel[barNum].posY))
                            return barNum;
                    }
                }
            }
        }
    }

    return -1;
}

int checkHCollision(int hamXleft, int hamYtop, int barXleft, int barYtop) { /* Returns 1 if the Barrel Collides with the Hammer, 0 if not*/

    /* Set Marios Collider */
    int hamXright = hamXleft + 15;
    int hamYbottom = hamYtop + 15;

    /* Set Other Objects Collider */
    int barXright = barXleft + 15;
    int barYbottom = barYtop + 15;
    
    
    if (hamXleft > barXleft && hamXleft < barXright || hamXright > barXleft && hamXright < barXright) {
        if (hamYtop < barYbottom && hamYtop > barYtop || hamYbottom < barYbottom && hamYbottom > barYtop) {
            return 1;
        }
    }
    else {
        return 0;   
    }
}

int checkBarrelJumped(Mario mario, Barrel barrel[]) {

    int barNum;

    for (barNum = 0; barNum < 9; barNum++) {
        if (checkJZCollision(mario.posX, mario.posY, barrel[barNum].posX, barrel[barNum].posY)) {
            return 1;
        }
    }

    return 0;
}

int checkJZCollision(int jmXleft, int jmYtop, int barXleft, int barYtopOld) { /* Returns 1 if Mario jumped over a Barrel, 0 otherwise */

    /* Set Marios Collider */
    int jmXright = jmXleft + 15;
    int jmYbottom = jmYtop + 15;

    /* Set Barrel "Jump Zone" */
    int barYtop = barYtopOld - 16;
    int barXright = barXleft + 15;
    int barYbottom = barYtop + 15;
    
    
    if (jmXleft > barXleft && jmXleft < barXright || jmXright > barXleft && jmXright < barXright) {
        if (jmYtop < barYbottom && jmYtop > barYtop || jmYbottom < barYbottom && jmYbottom > barYtop) {
            return 1;
        }
    }
    else {
        return 0;   
    }
}