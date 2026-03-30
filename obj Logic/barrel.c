#include "barrel.h"

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