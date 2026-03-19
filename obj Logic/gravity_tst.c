#include "stdio.h"
#include <osbind.h>
#include "raster.c" /* Changing this from .h to .c */

#include "gravity.h"
#include "model.h"
#include "girder.h" 
#include "rGirder.c" /* Changing this from .h to .c */
#include "mario.h"
#include "rMario.c"

void not_grounded(Girder girder, Mario mario, UINT32 *base) {

    /*
    
    Case 1: Mario is right above a girder
            Expected behavior: return false

    Case 2: Mario is above girders but none of them are right under him
            Expected behavior: return false
    
    */

    clear_screen(base);

    renderGirder(girder, base);
    renderMario(mario, base);

}

void grounded() {

}

int main() {

    UINT32 *base = Physbase();

    Girder test_girder_1 = {1, 192, 202, 0, 3, 0, 0};
    Mario test_mario_1 = {1, 218, 160, 0, 0, 3, 0, 0, -1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 306, 322, 300, 316};

    not_grounded(test_girder_1, test_mario_1, base);
    

    return 0;
}