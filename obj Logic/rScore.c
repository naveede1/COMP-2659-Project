#include "rScore.h"

void renderScore(Score score, UINT32 *base) {

    /*
    char highScore[12];
    char currScore{12};
    */

    linea0();
    

    if (score.visible == 1){

        plot_string(base, score.posY, score.posX, "HIGH SCORE");
    
        /*
        score_int_to_string(score.highScore, highScore);
        plot_string(base, score.posY + 15, score.posX + 16, highScore);

        score_int_to_string(score.value, currScore);
        plot_string(base, 186, 32, currScore);
        */
    }
}

void score_int_to_string(INT32 value, char *buffer) {
    INT32 temp;
    INT16 i = 0;
    INT16 j;
    INT16 is_negative = 0;

    if (value == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (value < 0)
    {
        is_negative = 1;
        value = -value;
    }

    /* Convert digits (reversed order) */
    while (value > 0)
    {
        temp = value % 10;
        buffer[i++] = (char)('0' + temp);
        value = value / 10;
    }

    if (is_negative)
        buffer[i++] = '-';

    buffer[i] = '\0';

    /* Reverse the string */
    for (j = 0; j < i / 2; j++)
    {
        char t = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = t;
    }
}