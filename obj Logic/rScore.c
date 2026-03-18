#include "rScore.h"

#include <stdio.h>

char currScore[7];
char highScore[7];

void longToStr(long val, char *str){
	
    int i = 5;
    
    while(i > -1){
		str[i--] = val % 10 + '0';
		val /= 10;
	}
}

void renderScore(Score score, UINT32 base) {
    
    linea0();

    if (score.visible == 1){

        plot_string(base, score.posY, score.posX, "HIGH SCORE");
        
        longToStr(score.value, currScore);
        currScore[6] = '\0';

        plot_string(base, score.posY+16, score.posX-62, currScore);
        
        longToStr(score.highValue, highScore);
        highScore[6] = '\0';

        plot_string(base, score.posY+16, score.posX+16, highScore);
    }
}

