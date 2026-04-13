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

            } else if (spawnedTime >= 250 && spawnedTime < 650) {

                if (barrel[i].dropTick == 4) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX += 4;
                barrel[i].dropTick++;
                
            } else if (spawnedTime >= 650 && spawnedTime < 800){

                barrel[i].posY += 6;
                barrel[i].dropTick = 2;

            } else  if (spawnedTime >= 800 && spawnedTime < 1160) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX -= 8;
                barrel[i].dropTick++;
            
            } else if (spawnedTime >= 1520 && spawnedTime < 1700){

                barrel[i].posY += 4;
                barrel[i].dropTick = 2;

            } else if (spawnedTime >= 1700 && spawnedTime < 2145) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX += 8;
                barrel[i].dropTick++;

            } else if (spawnedTime >= 2145 && spawnedTime < 2360){

                barrel[i].posX += 4;
            
            } else if (spawnedTime >= 2360 && spawnedTime < 2475){

                barrel[i].posY += 6;
                barrel[i].dropTick = 2;                

            } else if (spawnedTime >= 2475 && spawnedTime < 3000) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX -= 8;
                barrel[i].dropTick++;
        
            } else if (spawnedTime >= 3000 && spawnedTime < 3200){

                barrel[i].posY += 4;
                barrel[i].dropTick = 2;
            
            } else if (spawnedTime >= 3200 && spawnedTime < 3600) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                }     
                barrel[i].posX += 8;
                barrel[i].dropTick++;

            } else if (spawnedTime >= 3600 && spawnedTime < 3800){

                barrel[i].posX += 4;
            
            } else if (spawnedTime >= 3800 && spawnedTime < 4000){

                barrel[i].posY += 2;
                barrel[i].dropTick = 2;        
        
            } else if (spawnedTime >= 4000 && spawnedTime < 4820) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++; /* Barrel falls one girder */
                    barrel[i].dropTick = 0;
                } 
                barrel[i].posX -= 8;
                barrel[i].dropTick++;
            
            } else if (spawnedTime > 4820) {

                barrel[i].visible = 0;
                barrel[i].timeSpawned = 0;
            
            } else {

                barrel[i].posX -= 4;

            }
        }
    }

    return;
}