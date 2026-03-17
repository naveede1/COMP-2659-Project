#include "rScore.h"

char* intToString(int value) {

    static char score[7];  /* 6 digits + null terminator */
    int divisor = 100000;  /* for 6-digit scores */
    int i;

    for (i = 0; i < 6; i++) {
        int digit = value / divisor;
        score[i] = '0' + digit;
        value = value % divisor;
        divisor /= 10;
    }

    score[6] = '\0'; /* null terminate the string */
    return score;
}

void renderScore(Score score, UINT32 base) {

    char* highScore;
    char* currScore;
    
    linea0();

    if (score.visible == 1){

        printf("%s\n", intToString(score.value));

        plot_string(base, score.posY, score.posX, "HIGH SCORE");
        
        currScore = intToString(score.value);
        plot_string(base, score.posY+16, score.posX-62, currScore);

        highScore = intToString(score.highValue);
        plot_string(base, score.posY+16, score.posX+16, highScore);

    }
}

