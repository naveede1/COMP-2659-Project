#include "rMain.c"
#include "tstMod.c"

#include <osbind.h>
#include <stdio.h>

int main() {

    UINT32 *base = Physbase(); 
    Model *model; 

    model = &testModel1;
    render(model, base); /* Render Test Model 1 - Playing and Jumping */
    Cnecin();
    testMario(model->mario);
    Cnecin();
    testKong(model->kong);
    Cnecin();


    model = &testModel2;
    render(model, base); /* Render Test Model 2 -  Died to Barrel */
    Cnecin();
    testMario(model->mario);
    Cnecin();
    testSpirit(model->spirit);
    Cnecin();


    model = &testModel3;
    render(model, base); /* Render Test Model 3 - Victory */
    Cnecin();
    testMario(model->mario);
    Cnecin();
    testLady(model->lady);
    Cnecin();
   
    return 0;
}