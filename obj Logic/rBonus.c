#include "rBonus.h"

#include <stdio.h>

char currTimer[5];

void intToStr(int val, char *str){ /* Casts Integer Value into an Array of Chars */
	
    int i = 3; /* Casts 4 digit numbers*/
    
    while(i > -1){
		str[i--] = val % 10 + '0';
		val /= 10;
	}
}

void renderBonus(Timer timer, UINT32 base) {

    linea0();

    if (timer.visible == 1){

        linea0();
        plot_string(base, timer.posY - 4, timer.posX, "BONUS");  

        intToStr(timer.value, currTimer);
        currTimer[4] = '\0';

        plot_string(base, timer.posY + 11, timer.posX + 4, currTimer);

        plot_bitmap_32(base, timer.posY - 2, timer.posX - 4, 32, bonus_leftBM);
        plot_bitmap_32(base, timer.posY - 2, timer.posX + 28, 32, bonus_rightBM);
    }
} 