#include "rScore.h"

void renderScore(Score score, UINT32 base) {

    /*
    char highScore[12];
    char currScore{12};
    */

    linea0();
    

    if (score.visible == 1){

        plot_string(base, score.posY, score.posX, "HIGH SCORE");
    
        /*score_int_to_string(score.highScore, highScore); */
        plot_string(base, score.posY + 15, score.posX + 16, "070981");

        /*score_int_to_string(score.value, currScore);*/
        plot_string(base, score.posY + 17, score.posX - 62, "019600");
        
    }
}
