#include "stdio.h"
#include <osbind.h>
#include "raster.c" /* Changing this from .h to .c */

#include "gravity.h"
#include "model.h"
#include "girder.h" 
#include "rGirder.c" /* Changing this from .h to .c */
#include "mario.h"
#include "rMario.h"

void not_grounded() {

    /*
    
    Case 1: Mario is right above a girder
            Expected behavior: return false

    Case 2: Mario is above girders but none of them are right under him
            Expected behavior: return false
    
    */

}

void grounded() {

}

int main() {

    UINT32 *base = Physbase();

    Girder test_girder_1 = { 1, 192, 202, 0, 3, 0, 0};

    clear_screen(base);
    renderGirder(test_girder_1, base);

    return 0;
}