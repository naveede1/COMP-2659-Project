#include "model.h"
#include "raster.h"
#include <osbind.h>
#include <linea.h>
#include <stdio.h>

void posToStr(int val, char *str){ /* Casts Long Values into Arrays of Chars */
	
    int i = 2; /* Casts 3 digit numbers*/
    
    while(i > -1){
		str[i--] = val % 10 + '0';
		val /= 10;
	}
}


/* Updates the Bounds of Marios collider*/
void updateMBounds(Mario *mario) {

    mario->leftB = mario->posX + 1;
    mario->rightB = mario->posX + 14;
    mario->topB = mario->posY;
    mario->bottomB = mario->posY + 15;
    mario->centerX = mario->posX + 7;
    mario->centerY = mario->posY + 7;

}

void printMColliderInfo(Mario mario, UINT32 *base) {

    char position[4];
    linea0();

    plot_string((UINT8 *)base, 18, 14, "MBounds (LRTB)");

    posToStr(mario.leftB, position);
    position[3] = '\0';
    plot_string((UINT8 *)base, 36, 14, position);

    posToStr(mario.rightB, position);
    position[3] = '\0';
    plot_string((UINT8 *)base, 54, 14, position);
    
    posToStr(mario.topB, position);
    position[3] = '\0';
    plot_string((UINT8 *)base, 72, 14, position);

    posToStr(mario.bottomB, position);
    position[3] = '\0';
    plot_string((UINT8 *)base, 90, 14, position);

}

void printLadderColliderInfo(Ladder ladder, UINT32 *base) {

    char position[4];
    linea0();

    plot_string((UINT8 *)base, 112, 14, "LBounds (LRTB)");

    posToStr(ladder.leftB, position);
    position[3] = '\0';
    plot_string((UINT8 *)base, 130, 14, position);

    posToStr(ladder.rightB, position);
    position[3] = '\0';
    plot_string((UINT8 *)base, 148, 14, position);
    
    posToStr(ladder.topB, position);
    position[3] = '\0';
    plot_string((UINT8 *)base, 166, 14, position);

    posToStr(ladder.bottomB, position);
    position[3] = '\0';
    plot_string((UINT8 *)base, 184, 14, position);

}

void printHammerColliderInfo(Hammer hammer, UINT32 *base) {

    char position[4];
    linea0();

    plot_string((UINT8 *)base, 112, 14, "HBounds (LRTB)");

    posToStr(hammer.leftB, position);
    position[3] = '\0';
    plot_string((UINT8 *)base, 130, 14, position);

    posToStr(hammer.rightB, position);
    position[3] = '\0';
    plot_string((UINT8 *)base, 148, 14, position);
    
    posToStr(hammer.topB, position);
    position[3] = '\0';
    plot_string((UINT8 *)base, 166, 14, position);

    posToStr(hammer.bottomB, position);
    position[3] = '\0';
    plot_string((UINT8 *)base, 184, 14, position);

}

int ladderCollision (Mario *mario, Ladder ladder, int index) {
    if (ladder.broken || mario->hammerActive)
        return 0;
    if (mario->centerX >= ladder.leftB && mario->centerX <= ladder.rightB) {
        if (mario->centerY >= ladder.topB && mario->centerY <= ladder.bottomB) {
            mario->ladderIndex = index;
            return 1;

        } else {
            return 0;

        }
    } else {
        return 0;
    }
}

int hammerCollision (Mario *mario, Hammer hammer, int index) {
    if (!hammer.visible) /* Can't recollect a collected hammer */
        return 0;
    if (mario->centerX >= hammer.leftB && mario->centerX <= hammer.rightB) {
        if (mario->centerY >= hammer.topB && mario->centerY <= hammer.bottomB) {
            mario->hammerIndex = index;
            return 1;

        } else {
            return 0;
        }

    } else {
        return 0;
    }
}

